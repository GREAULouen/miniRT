/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:05:57 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/24 19:27:37 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Computes the total intensity of light at the intersection with
 * the object
 *
 * @param intersect Point = Ray.og + intersect * Ray.dir
 * @param ray
 * @param obj
 * @return uint32_t
 */
uint32_t	compute_light(double intersect, t_vector3 *ray, t_scene_object *obj)
{
	t_program	*program;
	t_vector3	*point_to_light;
	t_vector3	*point;
	t_vector3	*normal;
	double		dot;
	double		total_intensity;
	uint32_t	total_color;
	int			index;

	program = get_program();
	total_intensity = 0.0;
	total_color = 0x0;
	index = -1;
	point = sol_to_point(intersect, ray, get_object(CAMERA)->s_camera.pos);
	normal = get_obj_normal()[obj->type](point, obj);
	dot = 0.0;
	while (++index < program->object_count)	// TODO: add pre-processing to have an array of Lights for simpler loops
	{
		if ((int) program->objects[index].type == AMBIENT_LIGHT)
		{
			total_intensity += program->objects[index].s_ambient_light.intensity;
			total_color = color_add_scal(total_color, program->objects[index].s_ambient_light.intensity, program->objects[index].s_ambient_light.color);
		}
		else if ((int) program->objects[index].type == SPOT_LIGHT && !is_in_shadow(point, program->objects[index].s_spot_light.pos))
		{
			point_to_light = ft_v3_dir(point, program->objects[index].s_spot_light.pos);
			dot = ft_dot_product(point_to_light, normal);
			if (dot > 0)
			{
				total_intensity += program->objects[index].s_spot_light.intensity * dot / (ft_v3_length(normal) * ft_v3_length(point_to_light));
				total_color = color_add_scal(total_color, program->objects[index].s_spot_light.intensity * dot / (ft_v3_length(normal) * ft_v3_length(point_to_light)), program->objects[index].s_spot_light.color);
			}
			free(point_to_light);
		}
	}
	free(point);
	free(normal);
	return (color_scal_mult(color_add(obj->s_sphere.color, total_color), total_intensity));
	// return (total_color); // UNCOMENT FOR TOTAL_LIGHT RESULT
}
