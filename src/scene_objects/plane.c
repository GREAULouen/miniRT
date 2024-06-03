/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:55:30 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/03 14:47:13 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	is_in_plane(double sol, t_vector3 *ray, t_vector3 *og, t_scene_object *obj)
{
	t_vector3 *pos;
	t_vector3 u;
	t_vector3 *v;
	t_vector3 *to_pos;

	pos = sol_to_point(sol, ray, og);
	if (fabs(obj->s_plane.normal->x) > fabs(obj->s_plane.normal->y))
		u = (t_vector3){-obj->s_plane.normal->z, 0.0, obj->s_plane.normal->x};
	else
		u = (t_vector3){0.0, obj->s_plane.normal->z, -obj->s_plane.normal->y};
	v = ft_v3_cross_product(&u, obj->s_plane.normal);
	ft_v3_innormalize(&u);
	ft_v3_innormalize(v);
	to_pos = ft_v3_dir(obj->s_plane.pos, pos);
	// print_v3("\nray", ray, ONELINE);
	// print_v3("  |- u", &u, ONELINE);
	// print_v3("  |- v", v, ONELINE);
	// print_v3("  |- local_pos", to_pos, ONELINE);
	if (fabs(ft_dot_product(to_pos, &u)) > obj->s_plane.width / 2.0 || fabs(ft_dot_product(to_pos, v)) > obj->s_plane.height / 2.0)
		return (free(v), free(to_pos), free(pos), 0);
	return (free(v), free(to_pos), free(pos), 1);
}

/**
 * @brief Initialize a plane using the args as values
 *
 * @param type
 * @param args
 * @return int : -1 if error else 0
 */
int	create_plane(t_scene_object *obj, int argc, char **args)
{
	if (argc < 4 || !args[1] || !args[2] || !args[3])
		return (rt_perror((char *)__func__, WRONG_ARGUMENT_COUNT), -1);
	obj->type = PLANE;
	obj->s_plane.pos = atov(args[1]);
	if (!obj->s_plane.pos)
		return (-1);
	obj->s_plane.normal = atov(args[2]);
	if (!obj->s_plane.normal)
		return (free(obj->s_plane.pos), -1);
	ft_v3_innormalize(obj->s_plane.normal);
	obj->color = atoc(args[3]);
	obj->s_plane.dot = ft_dot_product(obj->s_plane.pos, obj->s_plane.normal);
	obj->shininess = 0.0;
	if (argc >= 5)
		obj->shininess = ft_atod(args[4]);
	obj->reflectiveness = 0.0;
	if (argc >= 6)
		obj->reflectiveness = ft_atod(args[5]);
	obj->s_plane.is_finite = 0;
	if (argc >= 8)
	{
		obj->s_plane.is_finite = 1;
		obj->s_plane.width = ft_atod(args[6]);
		obj->s_plane.height = ft_atod(args[7]);
	}
	return (0);
}

void	cleanup_plane(t_scene_object *obj)
{
	if (!obj)
		return ;
	free(obj->s_plane.pos);
	free(obj->s_plane.normal);
}

double	intersect_plane(t_vector3 *og, t_vector3 *ray, t_scene_object *obj, int (*is_valid)(double))
{
	double	t;
	double	ray_n;
	double	og_n;

	ray_n = ft_dot_product(ray, obj->s_plane.normal);
	og_n = ft_dot_product(og, obj->s_plane.normal);
	if (fabs(ray_n) <= EPSILON)
		return (INFINITY);
	t = (obj->s_plane.dot - og_n) / ray_n;
	if (!is_valid(t) || (obj->s_plane.is_finite && !is_in_plane(t, ray, og, obj)))
		return (INFINITY);
	return (t);
}

t_vector3	*normal_plane(t_vector3 *og, t_vector3 *point, t_scene_object *obj)
{
	t_vector3	*p_og;
	t_vector3	*res;

	p_og = ft_v3_dir(og, point);
	if (ft_dot_product(p_og, obj->s_plane.normal) > 0)
	{
		res = ft_v3_mult(obj->s_plane.normal, -1.0);
		return (free(p_og), res);
	}
	return (free(p_og), ft_v3_cpy(obj->s_plane.normal));
}
