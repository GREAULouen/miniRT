/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_intersection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:06:23 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/31 13:13:05 by lgreau           ###   ########.fr       */
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
uint32_t	compute_intersection(t_vector3 *og, t_vector3 *ray, int depth, int (*is_valid)(double))
{
	t_program	*program;
	int			index;
	int			min;
	double		min_value;
	double		intersect;
	double		reflected_color;
	double		local_color;
	t_vector3	reflected;
	t_vector3	*point;
	t_vector3	*normal;

	program = get_program();
	index = -1;
	min = index;
	min_value = INFINITY;
	reflected = (t_vector3){0.0, 0.0, 0.0};
	while (++index < program->object_count)	// Can be changed to only test intersection with Solid objects that have been pre-processed
	{
		if ((int) program->objects[index].type > CAMERA)// || (int) program->objects[index].type == PLANE)	// Can be changed to only test intersection with Solid objects that have been pre-processed
		{
			intersect = get_obj_intersect()[program->objects[index].type](og, ray, &program->objects[index], is_valid);
			if (intersect != INFINITY && intersect < min_value)
			{
				min = index;
				min_value = intersect;
			}
		}
	}
	if (min < 0)
		return (BACKGROUND_COLOR);
	point = sol_to_point(min_value, ray, og, &program->objects[min]);
	normal = get_obj_normal()[program->objects[min].type](og, point, &program->objects[min]);
	// if (program->objects[min].type == CONE)
	// {
	// 	print_v3("\nray", ray, ONELINE);
	// 	printf("  |- sol: %f\n", min_value);
	// 	print_v3("point", point, ONELINE);
	// 	print_v3("normal", normal, ONELINE);
	// }
	reflected_ray(&(t_vector3){-ray->x, -ray->y, -ray->z}, normal, &reflected);
	local_color = compute_light(point, normal, &reflected, &program->objects[min]);
	if (program->objects[min].reflectiveness <= 0.0 || depth <= 0.0)
		return (free(point), free(normal), local_color);
	reflected_color = compute_intersection(point, &reflected, depth - 1, is_valid);
	if (reflected_color == BACKGROUND_COLOR)
		return (free(point), free(normal), local_color);
	return (free(point), free(normal), color_add(color_scal_mult(local_color, 1.0 - program->objects[min].reflectiveness), color_scal_mult(reflected_color, program->objects[min].reflectiveness)));
}

// ray: (0.015625, -0.118750, 0.714074)
//   |- a : 0.509449
//   |- b : -143.166653
//   |- c : 9955.555556
//   |- t1: 126.312923
//   |- t2: 154.709371

// ray: (0.015625, -0.118750, 0.714074)
//   |- sol: 126.312923
// point: (1.973639, -60.196774, 85.000340)
// normal: (0.032690, 0.069524, -0.997045)
