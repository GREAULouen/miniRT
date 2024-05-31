/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:50:58 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/31 17:11:19 by pgrossma         ###   ########.fr       */
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
int	create_cylinder(t_scene_object *obj, char **args)
{
	if (!args[1] || !args[2] || !args[3] || !args[4] || !args[5] || args[6])
		return (set_error((char *)__func__, INVALID_ARG), -1);
	obj->type = CYLINDER;
	obj->s_cylinder.pos = atov(args[1]);
	if (!obj->s_cylinder.pos)
		return (-1);
	obj->s_cylinder.dir = atov(args[2]);
	if (!obj->s_cylinder.dir)
		return (free(obj->s_cylinder.pos), -1);
	if (ft_dot_product(obj->s_cylinder.dir, obj->s_cylinder.dir) > 1)
		return (free(obj->s_cylinder.pos), free(obj->s_cylinder.dir),
			set_error((char *)__func__, INVALID_ARG), -1);
	obj->s_cylinder.diameter = ft_atod(args[3]);
	if (obj->s_cylinder.diameter < 0)
		return (free(obj->s_cylinder.pos), free(obj->s_cylinder.dir),
			set_error((char *)__func__, INVALID_ARG), -1);
	obj->s_cylinder.sq_rad = obj->s_cylinder.diameter * obj->s_cylinder.diameter / 4.0;
	obj->s_cylinder.height = ft_atod(args[4]);
	if (obj->s_cylinder.height < 0)
		return (free(obj->s_cylinder.pos), free(obj->s_cylinder.dir),
			set_error((char *)__func__, INVALID_ARG), -1);
	obj->s_cylinder.color = atoc(args[5]);
	update_ends(obj);
	return (0);
}

void	update_ends(t_scene_object *obj)
{
	obj->s_cylinder.end1 = ft_v3_mult(obj->s_cylinder.pos, obj->s_cylinder.height / 2.0);
	obj->s_cylinder.end2 = ft_v3_mult(obj->s_cylinder.pos, -(obj->s_cylinder.height / 2.0));
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
		t11 = ft_dot_product(obj->s_cylinder.dir, ft_v3_sub(ft_v3_mult(ray, t1), obj_org_pos));
		if (t11 < 0 || t11 > obj->s_cylinder.height)
			t1 = INFINITY;
	}
	t2 = 1.0 * (ft_dot_product(cross_ray_dir, cross_pos_dir) - sqrt(delta)) / ft_dot_product(cross_ray_dir, cross_ray_dir);
	if (!is_valid(t2))
		t2 = INFINITY;
	else
	{
		t22 = ft_dot_product(obj->s_cylinder.dir, ft_v3_sub(ft_v3_mult(ray, t2), obj_org_pos));
		if (t22 < 0 || t22 > obj->s_cylinder.height)
			t2 = INFINITY;
	}
	return (closest_intersection(t1, t2, ray, og));
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
