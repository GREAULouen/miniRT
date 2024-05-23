/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:10:17 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/23 17:01:02 by lgreau           ###   ########.fr       */
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
	int			row;
	int			col;
	uint32_t	pixel_color;

	row = -1;
	program = get_program();
	ray.z = get_object(CAMERA)->s_camera.view_plane;
	// printf("%f\n", program->viewport_height);
	while (++row < program->canvas_height)
	{
		ray.y = (program->viewport_height / 2.0) - (((double)row) * program->viewport_height / ((double) program->canvas_height));
		col = -1;
		while (++col < program->canvas_width)
		{
			ray.x = ((double) col) * program->viewport_width / ((double) program->canvas_width) - program->viewport_width / 2.0;
			// printf("ray @ [%d, %d]", row, col);
			// print_v3("", &ray, ONELINE);
			pixel_color = intersect_ray(&ray);
			mlx_put_pixel(program->image, col, row, (pixel_color << 8 | 255));
		}
	}
}

uint32_t	intersect_ray(t_vector3 *ray)
{
	t_program	*program;
	uint32_t	color;
	int			index;

	program = get_program();
	index = -1;
	while (++index < program->object_count)
	{
		if ((int) program->objects[index].type == SPHERE)
		{
			color = intersect_sphere(ray, &program->objects[index]);
			if (color != NO_INTERSECTION)
				return (color);
		}
	}
	return (BACKGROUND_COLOR);
}
