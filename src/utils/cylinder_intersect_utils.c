/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersect_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:09:43 by pgrossma          #+#    #+#             */
/*   Updated: 2024/06/04 18:48:25 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	intersect_endcaps_valid(double distance, t_vector3 *end, t_vector3 *ray, t_scene_object *obj)
{
	t_vector3	*ray_distance;
	bool		isvalid;

	ray_distance = ft_v3_mult(ray, distance);
	if (ray_distance == NULL)
		return (false);
	ft_v3_insub(ray_distance, end);
	isvalid = ft_dot_product(ray_distance, ray_distance) < obj->s_cylinder.sq_rad;
	free(ray_distance);
	return (isvalid);
}

double intersect_cylinder_endcaps(t_vector3 *og, t_vector3	*obj_org_pos, t_vector3 *ray, t_scene_object *obj)
{
	double		dot_dir_ray;
	double		distance[2];
	t_vector3	*end2;

	dot_dir_ray = ft_dot_product(obj->s_cylinder.dir, ray);
	if (dot_dir_ray == 0)
		return (-1);
	distance[0] = ft_dot_product(obj->s_cylinder.dir, obj_org_pos) / dot_dir_ray;
	if (!intersect_endcaps_valid(distance[0], obj_org_pos, ray, obj))
		distance[0] = INFINITY;
	end2 = ft_v3_mult(obj->s_cylinder.dir, obj->s_cylinder.height);
	if (end2 == NULL)
		return (0);
	ft_v3_inadd(end2, obj_org_pos);
	distance[1] = ft_dot_product(obj->s_cylinder.dir, end2) / dot_dir_ray;
	if (!intersect_endcaps_valid(distance[1], end2, ray, obj))
		distance[1] = INFINITY;
	return (closest_intersection(distance[0], distance[1], ray, og));
}

static double	closest_intersection_cylinder(t_is_cylinder *is_cylinder, int (*is_valid)(double))
{
	is_cylinder->t[0] = (is_cylinder->dot_crossraydir_crossposdir + is_cylinder->delta) / is_cylinder->dot_crossraydir;
	if (!is_valid(is_cylinder->t[0]))
		is_cylinder->t[0] = INFINITY;
	else
	{
		is_cylinder->t[1] = signed_distance_t_cylinder(is_cylinder->obj_org_pos, is_cylinder->ray, is_cylinder->obj, is_cylinder->t[0]);
		if (is_cylinder->t[1] < 0 || is_cylinder->t[1] > is_cylinder->obj->s_cylinder.height)
			is_cylinder->t[0] = INFINITY;
	}
	is_cylinder->t[2] = (is_cylinder->dot_crossraydir_crossposdir - is_cylinder->delta) / is_cylinder->dot_crossraydir;
	if (!is_valid(is_cylinder->t[2]))
		is_cylinder->t[2] = INFINITY;
	else
	{
		is_cylinder->t[3] = signed_distance_t_cylinder(is_cylinder->obj_org_pos, is_cylinder->ray, is_cylinder->obj, is_cylinder->t[2]);
		if (is_cylinder->t[3] < 0 || is_cylinder->t[3] > is_cylinder->obj->s_cylinder.height)
			is_cylinder->t[2] = INFINITY;
	}
	return (closest_intersection(is_cylinder->t[0], is_cylinder->t[2], is_cylinder->ray, is_cylinder->og));
}

double	intersect_cylinder_side(t_is_cylinder *is_cylinder, int (*is_valid)(double))
{
	is_cylinder->cross_ray_dir = ft_v3_cross_product(is_cylinder->ray, is_cylinder->obj->s_cylinder.dir);
	is_cylinder->dot_crossraydir = ft_dot_product(is_cylinder->cross_ray_dir, is_cylinder->cross_ray_dir);
	is_cylinder->cross_pos_dir = ft_v3_cross_product(is_cylinder->obj_org_pos, is_cylinder->obj->s_cylinder.dir);
	is_cylinder->dot_dir = ft_dot_product(is_cylinder->obj->s_cylinder.dir, is_cylinder->obj->s_cylinder.dir);
	is_cylinder->dot_pos_cross_ray_dir = ft_dot_product(is_cylinder->obj_org_pos, is_cylinder->cross_ray_dir);
	is_cylinder->delta = is_cylinder->dot_crossraydir * is_cylinder->obj->s_cylinder.sq_rad - is_cylinder->dot_dir * (is_cylinder->dot_pos_cross_ray_dir * is_cylinder->dot_pos_cross_ray_dir);
	if (is_cylinder->delta < 0)
		return (INFINITY);
	is_cylinder->delta = sqrt(is_cylinder->delta);
	is_cylinder->dot_crossraydir_crossposdir = ft_dot_product(is_cylinder->cross_ray_dir, is_cylinder->cross_pos_dir);
	return (closest_intersection_cylinder(is_cylinder, is_valid));
}
