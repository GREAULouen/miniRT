/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_intersection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:06:23 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/28 18:57:10 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Computes if there's an intersection with any solid object in the scene
 * & returns the computed light
 *
 * @param ray
 * @return uint32_t
 */
uint32_t	compute_intersection(t_vector3 *ray)
{
	t_program	*program;
	int			index;
	int			min;
	double		min_value;
	double		intersect;

	program = get_program();
	index = -1;
	min = index;
	min_value = INFINITY;
	while (++index < program->object_count)	// Can be changed to only test intersection with Solid objects that have been pre-processed
	{
		if ((int) program->objects[index].type == SPHERE || (int) program->objects[index].type == PLANE || (int) program->objects[index].type == CYLINDER)	// Can be changed to only test intersection with Solid objects that have been pre-processed
		{
			// printf("Sphere x = %f\n", program->objects[index].s_sphere.pos->x);
			intersect = get_obj_intersect()[program->objects[index].type](get_object(CAMERA)->s_camera.pos, ray, &program->objects[index], valid_sol_from_cam);
			// if (program->objects[index].s_sphere.pos->z == 0.0)
			if (intersect != INFINITY && intersect < min_value)
			{
				printf("intersect test: %f\n", intersect);
				min = index;
				min_value = intersect;
			}
		}
	}
	if (min_value < INFINITY)
		return (compute_light(min_value, ray, &program->objects[min]));
	return (color_scal_mult(get_object(AMBIENT_LIGHT)->s_ambient_light.color, get_object(AMBIENT_LIGHT)->s_ambient_light.intensity));
}
