/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_distance_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:16:41 by pgrossma          #+#    #+#             */
/*   Updated: 2024/06/04 19:23:15 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	signed_distance_t_cylinder(t_vector3 *og, t_vector3 *ray,
		t_scene_object *obj, double distance)
{
	t_vector3	*mult_ray_distance;
	double		signed_distance;

	mult_ray_distance = ft_v3_mult(ray, distance);
	if (mult_ray_distance == NULL)
		return (0);
	ft_v3_insub(mult_ray_distance, og);
	signed_distance = ft_dot_product(obj->s_cylinder.dir, mult_ray_distance);
	free(mult_ray_distance);
	return (signed_distance);
}

double	signed_distance_t_cylinder_point(t_vector3 *point, t_vector3 *og,
		t_scene_object *obj)
{
	t_vector3	*sub_mult_ray_distance_og;
	double		signed_distance;

	sub_mult_ray_distance_og = ft_v3_sub(point, og);
	if (sub_mult_ray_distance_og == NULL)
		return (0);
	signed_distance = ft_dot_product(obj->s_cylinder.dir,
			sub_mult_ray_distance_og);
	free(sub_mult_ray_distance_og);
	return (signed_distance);
}
