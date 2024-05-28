/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_intersection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:06:23 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/28 14:22:45 by lgreau           ###   ########.fr       */
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
		if ((int) program->objects[index].type == SPHERE || (int) program->objects[index].type == PLANE)	// Can be changed to only test intersection with Solid objects that have been pre-processed
		{
			intersect = get_obj_intersect()[program->objects[index].type](get_object(CAMERA)->s_camera.pos, ray, &program->objects[index], valid_sol_from_cam);
			if (intersect != INFINITY && intersect < min_value)
			{
				min = index;
				min_value = intersect;
			}
		}
	}
	if (min_value < INFINITY)
		return (compute_light(min_value, ray, &program->objects[min]));
	return (color_scal_mult(get_object(AMBIENT_LIGHT)->color, get_object(AMBIENT_LIGHT)->s_ambient_light.intensity));
}
