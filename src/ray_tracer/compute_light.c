/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:05:57 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/05 16:30:22 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	compute_specular_light(t_l_utils *utils, t_program *program,
	t_vector3 *point, t_vector3 *reflected)
{
	t_vector3	*point_to_cam;

	point_to_cam = ft_v3_dir(point, get_object(CAMERA)->s_camera.pos);
	utils->r_dot_c = ft_dot_product(reflected, point_to_cam);
	if (utils->r_dot_c > 0)
		utils->total_intensity += program->objects[utils->index]. \
			s_spot_light.intensity * pow(utils->r_dot_c
				/ (ft_v3_length(reflected) * ft_v3_length(point_to_cam)),
				utils->obj_shi);
	free(point_to_cam);
}

static void	compute_spot_light(t_l_utils *utils, t_vector3 *point,
	t_vector3 *normal, t_vector3 *reflected)
{
	t_program	*program;
	t_vector3	*point_to_light;

	program = get_program();
	point_to_light = ft_v3_dir(point,
			program->objects[utils->index].s_spot_light.pos);
	utils->n_dot_l = ft_dot_product(point_to_light, normal);
	if (utils->n_dot_l > 0)
	{
		utils->total_intensity += program->objects[utils->index]. \
			s_spot_light.intensity * utils->n_dot_l
			/ (ft_v3_length(point_to_light));
		utils->total_color = color_add_scal(utils->total_color,
				program->objects[utils->index].s_spot_light.intensity
				* utils->n_dot_l / (ft_v3_length(point_to_light)),
				program->objects[utils->index].color);
	}
	if (utils->obj_shi > 0.0)
		compute_specular_light(utils, program, point, reflected);
	free(point_to_light);
}

/**
 * @brief Computes the total intensity of light at the intersection with
 * the object
 *
 * @param intersect Point = Ray.og + intersect * Ray.dir
 * @param ray
 * @param obj
 * @return uint32_t
 */
uint32_t	compute_light(t_vector3 *point, t_vector3 *normal,
	t_vector3 *reflected, t_scene_object *obj)
{
	t_program	*program;
	t_l_utils	utils;

	program = get_program();
	utils = (t_l_utils){obj->shininess, 0.0, 0.0, 0.0, 0x0, -1};
	while (++utils.index < program->object_count)
	{
		if ((int) program->objects[utils.index].type == AMBIENT_LIGHT)
		{
			utils.total_intensity += program->objects[utils.index]. \
				s_ambient_light.intensity;
			utils.total_color = color_add_scal(utils.total_color,
					program->objects[utils.index].s_ambient_light.intensity,
					program->objects[utils.index].color);
		}
		else if ((int) program->objects[utils.index].type == SPOT_LIGHT
			&& !is_in_shadow(point, program->objects[utils.index]. \
				s_spot_light.pos))
			compute_spot_light(&utils, point, normal, reflected);
	}
	return (color_scal_mult(color_rem_opposite(utils.total_color, obj->color),
			utils.total_intensity));
}

void	reflected_ray(t_vector3 *ray, t_vector3 *normal, t_vector3 *res)
{
	double	dot;

	dot = ft_dot_product(ray, normal);
	res->x = 2 * dot * normal->x - ray->x;
	res->y = 2 * dot * normal->y - ray->y;
	res->z = 2 * dot * normal->z - ray->z;
}
