/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:10:17 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/05 16:30:25 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	rand_offset(t_program *program)
{
	if (program->max_image_buffering <= 0)
		return (0.0);
	return (((double) rand() / (double) RAND_MAX) - 0.5);
}

static void	rt_put_pixel(t_r_utils *utils, t_program *program)
{
	if (program->max_image_buffering > 0)
	{
		if (program->image_count == 1)
			program->avg_buffer[utils->row * program->canvas_width
				+ utils->col] = (t_vector3){0.0, 0.0, 0.0};
		if (program->image_count + 1 < program->max_image_buffering)
		{
			program->avg_buffer[utils->row * program->canvas_width
				+ utils->col].x += (double) get_red(utils->pixel_color);
			program->avg_buffer[utils->row * program->canvas_width
				+ utils->col].y += (double) get_green(utils->pixel_color);
			program->avg_buffer[utils->row * program->canvas_width
				+ utils->col].z += (double) get_blue(utils->pixel_color);
		}
		compute_final_color(utils->row, utils->col);
	}
	else
		mlx_put_pixel(program->image, utils->col, utils->row,
			(utils->pixel_color << 8) | 255);
}

static void	fill_col(t_r_utils *utils, t_program *program,
	t_scene_object *camera)
{
	utils->col = -1;
	while (++utils->col < program->canvas_width)
	{
		utils->ray.x = (((double) utils->col + rand_offset(program))
				* program->vc_width_ratio) - program->half_view_width;
		ft_apply_rotate(&utils->ray, &camera->s_camera.rot,
			&utils->tmp);
		utils->pixel_color = compute_intersection(camera-> \
			s_camera.pos, &utils->tmp, program->max_reflections,
				valid_sol_from_cam);
		rt_put_pixel(utils, program);
	}
}

/**
 * @brief Loops through the pixel on the screen, creating the corresponding ray
 * & giving it to a calculation function
 *
 */
void	*init_ray(void *arg)
{
	t_program		*program;
	t_scene_object	*camera;
	t_r_utils		utils;

	program = get_program();
	camera = get_object(CAMERA);
	utils = (t_r_utils){(t_vector3){0.0, 0.0, camera->s_camera. \
		view_plane}, (t_vector3){0.0, 0.0, 0.0}, 0, 0, 0};
	if (arg)
		utils.row = *(int *)arg;
	else
		utils.row = 0;
	while (utils.row < program->canvas_height)
	{
		utils.ray.y = program->half_view_height - (((double)utils.row
					+ rand_offset(program)) * program->vc_height_ratio);
		fill_col(&utils, program, camera);
		utils.row += (program->thread_count) + (program->thread_count <= 0);
	}
	return (NULL);
}
