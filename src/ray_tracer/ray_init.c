/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:10:17 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/03 12:47:50 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	rand_offset(void)
{
	return (((double) rand() / (double) RAND_MAX) - 0.5);
}

/**
 * @brief Loops through the pixel on the screen, creating the corresponding ray
 * & giving it to a calculation function
 *
 */
void	init_ray(void)
{
	t_program	*program;
	t_vector3	ray;
	t_vector3	tmp;
	int			row;
	int			col;
	uint32_t	pixel_color;

	row = -1;
	program = get_program();
	ray.z = get_object(CAMERA)->s_camera.view_plane;
	while (++row < program->canvas_height)
	{
		ray.y = program->half_view_height - (((double)row + rand_offset()) * program->vc_height_ratio);
		col = -1;
		while (++col < program->canvas_width)
		{
			ray.x = (((double) col + rand_offset()) * program->vc_width_ratio) - program->half_view_width;
			ft_apply_rotate(&ray, &get_object(CAMERA)->s_camera.rot, &tmp);
			pixel_color = compute_intersection(get_object(CAMERA)->s_camera.pos, &tmp, program->max_reflections, valid_sol_from_cam);
			// if (!ANTI_ALIASING)
			// 	mlx_put_pixel(program->image, col , row, (pixel_color << 8) | 255);
			// else
			// {
				// program->image_buffer[program->image_count][row * program->canvas_width + col] = pixel_color;
			if (program->image_count == 1)
				program->avg_buffer[row * program->canvas_width + col] = (t_vector3){0.0, 0.0, 0.0};
			if (program->image_count + 1 < IMG_BUFFER_COUNT)
			{
				program->avg_buffer[row * program->canvas_width + col].x += (double) get_red(pixel_color);
				program->avg_buffer[row * program->canvas_width + col].y += (double) get_green(pixel_color);
				program->avg_buffer[row * program->canvas_width + col].z += (double) get_blue(pixel_color);
			}
			compute_final_color(row, col);
			// }
		}
	}
}
