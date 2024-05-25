/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:10:17 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/25 12:54:30 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
		ray.y = (program->viewport_height / 2.0) - (((double)row) * program->viewport_height / ((double) program->canvas_height));
		col = -1;
		while (++col < program->canvas_width)
		{
			ray.x = (program->viewport_width / 2.0) - (((double) col) * program->viewport_width / ((double) program->canvas_width));
			rotate_ray(&ray, &tmp);
			// ft_v3_inadd(&tmp, get_object(CAMERA)->s_camera.pos);
			pixel_color = compute_intersection(&tmp);
			mlx_put_pixel(program->image, col, row, (pixel_color << 8 | 255));
		}
	}
}

/**
 * @brief Rotates the ray to match the direction of the camera
 *
 * @param ray
 */
void	rotate_ray(t_vector3 *ray, t_vector3 *res)
{
	t_matrix	*rot;

	rot = &get_object(CAMERA)->s_camera.rot;
	res->x = ray->x * (*rot)[0][0] + ray->y * (*rot)[0][1] + ray->z * (*rot)[0][2];
	res->y = ray->x * (*rot)[1][0] + ray->y * (*rot)[1][1] + ray->z * (*rot)[1][2];
	res->z = ray->x * (*rot)[2][0] + ray->y * (*rot)[2][1] + ray->z * (*rot)[2][2];
}
