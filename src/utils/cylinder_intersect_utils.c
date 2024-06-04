/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersect_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:09:43 by pgrossma          #+#    #+#             */
/*   Updated: 2024/06/04 18:16:28 by pgrossma         ###   ########.fr       */
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

double	intersect_cylinder_side(t_vector3 *og, t_vector3 *obj_org_pos, t_vector3 *ray, t_scene_object *obj, int (*is_valid)(double))
{
	double		delta;
	double		t1;
	double		t11;
	double		t2;
	double		t22;
	t_vector3	*cross_ray_dir;
	t_vector3	*cross_pos_dir;
	double		dot_dir;
	double		dot_pos_cross_ray_dir;
	double		dot_crossraydir;
	double		dot_crossraydir_crossposdir;

	cross_ray_dir = ft_v3_cross_product(ray, obj->s_cylinder.dir);
	dot_crossraydir = ft_dot_product(cross_ray_dir, cross_ray_dir);
	cross_pos_dir = ft_v3_cross_product(obj_org_pos, obj->s_cylinder.dir);
	dot_dir = ft_dot_product(obj->s_cylinder.dir, obj->s_cylinder.dir);

	dot_pos_cross_ray_dir = ft_dot_product(obj_org_pos, cross_ray_dir);

	delta = dot_crossraydir * obj->s_cylinder.sq_rad - dot_dir * (dot_pos_cross_ray_dir * dot_pos_cross_ray_dir);
	if (delta < 0)
		return (INFINITY);
	delta = sqrt(delta);
	dot_crossraydir_crossposdir = ft_dot_product(cross_ray_dir, cross_pos_dir);
	t1 = 1.0 * (dot_crossraydir_crossposdir + delta) / dot_crossraydir;
	if (!is_valid(t1))
		t1 = INFINITY;
	else
	{
		t11 = signed_distance_t_cylinder(obj_org_pos, ray, obj, t1);
		if (t11 < 0 || t11 > obj->s_cylinder.height)
			t1 = INFINITY;
	}
	t2 = 1.0 * (dot_crossraydir_crossposdir - delta) / dot_crossraydir;
	if (!is_valid(t2))
		t2 = INFINITY;
	else
	{
		t22 = signed_distance_t_cylinder(obj_org_pos, ray, obj, t2);
		if (t22 < 0 || t22 > obj->s_cylinder.height)
			t2 = INFINITY;
	}
	return (closest_intersection(t1, t2, ray, og));
}
