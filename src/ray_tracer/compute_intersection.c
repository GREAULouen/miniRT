/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_intersection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:06:23 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/05 14:41:40 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	compute_closest_objet(t_utils *utils, t_vector3 *og,
	t_vector3 *ray, int (*is_valid)(double))
{
	t_program	*program;

	program = get_program();
	while (++utils->index < program->object_count)
	{
		if ((int) program->objects[utils->index].type > CAMERA)
		{
			utils->intersect = get_obj_intersect()[program->objects \
				[utils->index].type](og, ray, &program->objects[utils->index],
					is_valid);
			if (utils->intersect != INFINITY && utils->intersect
				< utils->min_value)
			{
				utils->min_index = utils->index;
				utils->min_value = utils->intersect;
			}
		}
	}
}

static uint32_t	mix_colors(t_utils *utils, t_program *program)
{
	return (color_add(color_scal_mult(utils->local_color,
				1.0 - program->objects[utils->min_index].reflectiveness),
			color_scal_mult(utils->reflected_color,
				program->objects[utils->min_index].reflectiveness)));
}

/**
 * @brief Computes if there's an intersection with any solid object in the scene
 * & returns the computed light
 *
 * @param ray
 * @return uint32_t
 */
uint32_t	compute_intersection(t_vector3 *og, t_vector3 *ray, int depth,
	int (*is_valid)(double))
{
	t_program	*program;
	t_utils		utils;
	t_vector3	*point;
	t_vector3	*normal;

	program = get_program();
	utils = (t_utils){-1, -1, INFINITY, INFINITY, 0x0, 0x0,
		(t_vector3){0.0, 0.0, 0.0}};
	compute_closest_objet(&utils, og, ray, is_valid);
	if (utils.min_index < 0)
		return (BACKGROUND_COLOR);
	point = sol_to_point(utils.min_value, ray, og);
	normal = get_obj_normal()[program->objects[utils.min_index].type](og, point,
			&program->objects[utils.min_index]);
	reflected_ray(&(t_vector3){-ray->x, -ray->y, -ray->z}, normal, &utils.refl);
	utils.local_color = compute_light(point, normal, &utils.refl,
			&program->objects[utils.min_index]);
	if (program->objects[utils.min_index].reflectiveness <= 0.0 || depth <= 0.0)
		return (free(point), free(normal), utils.local_color);
	utils.reflected_color = compute_intersection(point, &utils.refl,
			depth - 1, is_valid);
	if (utils.reflected_color == BACKGROUND_COLOR)
		return (free(point), free(normal), utils.local_color);
	return (free(point), free(normal), mix_colors(&utils, program));
}
