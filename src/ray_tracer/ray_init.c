/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:10:17 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/22 21:56:28 by pgrossma         ###   ########.fr       */
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
	t_vector3	*intersection;

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
			intersection = intersect_ray(&ray);
			if (intersection)
			{
				mlx_put_pixel(program->image, row, col, COLOR_G);
				free(intersection);
			}
		}
	}
}

t_vector3	*intersect_ray(t_vector3 *ray)
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
				return (intersection);
		}
	}
	return (NULL);
}
