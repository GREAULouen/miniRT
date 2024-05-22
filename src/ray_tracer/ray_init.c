/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:10:17 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/22 17:54:22 by lgreau           ###   ########.fr       */
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
			intersect_ray(&ray);
		}
	}
}

void	intersect_ray(t_vector3 *ray)
{
	t_program	*program;
	t_vector3	*intersection;
	int			index;

	program = get_program();
	index = -1;
	while (++index < program->object_count)
	{
		if ((int) program->objects[index].type == SPHERE)
		{
			intersection = intersect_sphere(ray, &program->objects[index]);
			if (intersection != NULL)
			{
				print_v3("ray that intersect", ray, ONELINE);
				free(intersection);
			}
		}
	}
}
