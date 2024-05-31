/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:50:58 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/31 18:24:21 by pgrossma         ###   ########.fr       */
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
	obj->s_cylinder.height = ft_atod(args[4]);
	if (obj->s_cylinder.height < 0)
		return (free(obj->s_cylinder.pos), free(obj->s_cylinder.dir),
			rt_perror((char *)__func__, HEIGHT_OUT_OF_RANGE), -1);
	obj->color = atoc(args[5]);
	return (0);
}

void	update_ends(t_scene_object *obj)
{
	obj->s_cylinder.end1 = ft_v3_mult(obj->s_cylinder.pos, obj->s_cylinder.height / 2.0);
	obj->s_cylinder.end2 = ft_v3_mult(obj->s_cylinder.pos, -(obj->s_cylinder.height / 2.0));
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

double	intersect_cylinder(t_vector3 *og, t_vector3 *ray, t_scene_object *obj, int (*is_valid)(double))
{
	double		delta;
	double		t1;
	double		t11;
	double		t2;
	double		t22;
	t_vector3	*cross_ray_dir;
	t_vector3	*cross_pos_dir;
	t_vector3	*obj_org_pos;
	double		dot_dir;
	double		dot_pos_cross_ray_dir;

	cross_ray_dir = ft_v3_cross_product(ray, obj->s_cylinder.dir);
	obj_org_pos = ft_v3_sub(obj->s_cylinder.pos, og);
	cross_pos_dir = ft_v3_cross_product(obj_org_pos, obj->s_cylinder.dir);
	dot_dir = ft_dot_product(obj->s_cylinder.dir, obj->s_cylinder.dir);

	dot_pos_cross_ray_dir = ft_dot_product(obj_org_pos, cross_ray_dir);

	delta = ft_dot_product(cross_ray_dir, cross_ray_dir) * obj->s_cylinder.sq_rad - dot_dir * (dot_pos_cross_ray_dir * dot_pos_cross_ray_dir);
	if (delta < 0)
		return (INFINITY);
	t1 = 1.0 * (ft_dot_product(cross_ray_dir, cross_pos_dir) + sqrt(delta)) / ft_dot_product(cross_ray_dir, cross_ray_dir);
	if (!is_valid(t1))
		t1 = INFINITY;
	else
	{
		t11 = signed_distance_t_cylinder(obj_org_pos, ray, obj, t1);
		if (t11 < 0 || t11 > obj->s_cylinder.height)
			t1 = INFINITY;
	}
	t2 = 1.0 * (ft_dot_product(cross_ray_dir, cross_pos_dir) - sqrt(delta)) / ft_dot_product(cross_ray_dir, cross_ray_dir);
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

/**
 * @brief Allocat & computes the normal vector at the point on the cylinder
 *
 * @param point
 * @return t_vector3*
 */
t_vector3	*normal_cylinder(t_vector3 *og, t_vector3 *point, t_scene_object *obj)
{
	t_vector3	*normal;
	double		signed_distance;
	t_vector3	*obj_org_pos;
	t_vector3	*sub_dir_pos;

	obj_org_pos = ft_v3_sub(obj->s_cylinder.pos, og);
	signed_distance = ft_dot_product(point, obj_org_pos);
	sub_dir_pos = ft_v3_sub(obj->s_cylinder.dir, obj_org_pos);
	normal = ft_v3_sub(point, sub_dir_pos);
	free(obj_org_pos);
	free(sub_dir_pos);
	ft_v3_innormalize(normal);
	return (normal);
}

void	cleanup_cylinder(t_scene_object *obj)
{
	if (!obj)
		return ;
	free(obj->s_cylinder.pos);
	free(obj->s_cylinder.dir);
	free(obj->s_cylinder.end1);
	free(obj->s_cylinder.end2);
}
