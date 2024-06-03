/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:50:58 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/03 20:05:27 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Initialize a cylinder using the args as values
 *
 * @param type
 * @param args
 * @return int : -1 if error else 0
 */
int	create_cylinder(t_scene_object *obj, int argc, char **args)
{
	if (argc < 6 || !args[1] || !args[2] || !args[3] || !args[4] || !args[5])
		return (rt_perror((char *)__func__, WRONG_ARGUMENT_COUNT), -1);
	obj->type = CYLINDER;
	obj->s_cylinder.pos = atov(args[1]);
	if (!obj->s_cylinder.pos)
		return (-1);
	obj->s_cylinder.dir = atov(args[2]);
	if (!obj->s_cylinder.dir)
		return (free(obj->s_cylinder.pos), -1);
	ft_v3_innormalize(obj->s_cylinder.dir);
	obj->s_cylinder.diameter = ft_atod(args[3]);
	if (obj->s_cylinder.diameter < 0)
		return (free(obj->s_cylinder.pos), free(obj->s_cylinder.dir),
			rt_perror((char *)__func__, DIAMETER_OUT_OF_RANGE), -1);
	obj->s_cylinder.sq_rad = obj->s_cylinder.diameter * obj->s_cylinder.diameter / 4.0;
	obj->s_cylinder.height = ft_atod(args[4]);
	if (obj->s_cylinder.height < 0)
		return (free(obj->s_cylinder.pos), free(obj->s_cylinder.dir),
			rt_perror((char *)__func__, HEIGHT_OUT_OF_RANGE), -1);
	obj->color = atoc(args[5]);
	return (0);
}


double	signed_distance_t_cylinder(t_vector3 *og, t_vector3 *ray, t_scene_object *obj, double distance)
{
	t_vector3	*mult_ray_distance;
	t_vector3	*sub_mult_ray_distance_og;
	double		signed_distance;

	mult_ray_distance = ft_v3_mult(ray, distance);
	sub_mult_ray_distance_og = ft_v3_sub(mult_ray_distance, og);
	signed_distance = ft_dot_product(obj->s_cylinder.dir, sub_mult_ray_distance_og);
	free(mult_ray_distance);
	free(sub_mult_ray_distance_og);
	return (signed_distance);
}

double	signed_distance_t_cylinder_point(t_vector3 *point, t_vector3 *og, t_scene_object *obj)
{
	t_vector3	*sub_mult_ray_distance_og;
	double		signed_distance;

	sub_mult_ray_distance_og = ft_v3_sub(point, og);
	if (sub_mult_ray_distance_og == NULL)
		return (0);
	signed_distance = ft_dot_product(obj->s_cylinder.dir, sub_mult_ray_distance_og);
	free(sub_mult_ray_distance_og);
	return (signed_distance);
}

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

double	intersect_cylinder(t_vector3 *og, t_vector3 *ray, t_scene_object *obj, int (*is_valid)(double))
{
	t_vector3	*obj_org_pos;
	double		distance_endcap;
	double		distance_side;

	obj_org_pos = ft_v3_sub(obj->s_cylinder.pos, og);
	distance_endcap = intersect_cylinder_endcaps(og, obj_org_pos, ray, obj);
	distance_side = intersect_cylinder_side(og, obj_org_pos, ray, obj, is_valid);
	return (closest_intersection(distance_endcap, distance_side, ray, og));
}

t_vector3	*normal_sides(double signed_distance, t_vector3 *point, t_scene_object *obj)
{
	t_vector3	*normal;
	t_vector3	*sub_dir_pos;
	t_vector3	*mult_dir_dis;

	mult_dir_dis = ft_v3_mult(obj->s_cylinder.dir, signed_distance);
	if (mult_dir_dis == NULL)
		return (NULL);
	sub_dir_pos = ft_v3_sub(point, mult_dir_dis);
	if (sub_dir_pos == NULL)
		return (free(mult_dir_dis), NULL);
	normal = ft_v3_sub(sub_dir_pos, obj->s_cylinder.pos);
	free(sub_dir_pos);
	free(mult_dir_dis);
	if (normal == NULL)
		return (NULL);
	ft_v3_innormalize(normal);
	return (normal);
}

/**
 * @brief Allocat & computes the normal vector at the point on the cylinder
 *
 * @param point
 * @return t_vector3*
 */
t_vector3	*normal_cylinder(t_vector3 *og, t_vector3 *point, t_scene_object *obj)
{
	double		signed_distance;

	(void) og;
	signed_distance = signed_distance_t_cylinder_point(point, obj->s_cylinder.pos, obj);
	if (signed_distance < 0.001111)
		return (ft_v3_mult(obj->s_cylinder.pos, -1));
	else if (signed_distance == obj->s_cylinder.height)
		return (ft_v3_cpy(obj->s_cylinder.pos));
	else
		return (normal_sides(signed_distance, point, obj));
}

void	cleanup_cylinder(t_scene_object *obj)
{
	if (!obj)
		return ;
	free(obj->s_cylinder.pos);
	free(obj->s_cylinder.dir);
}
