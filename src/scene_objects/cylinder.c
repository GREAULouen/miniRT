/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:50:58 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/28 18:53:04 by pgrossma         ###   ########.fr       */
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
	t_vector3	*oc;
	double		dot_org;
	double		dot_org_ray;
	double		dot_org_oc;
	double		k2;
	double		k1;
	double		k0;

	(void) is_valid;
	oc = ft_v3_sub(og, obj->s_cylinder.end1);
	dot_org = ft_dot_product(obj->s_cylinder.pos, obj->s_cylinder.pos);
	dot_org_ray = ft_dot_product(obj->s_cylinder.pos, ray);
	dot_org_oc = ft_dot_product(obj->s_cylinder.pos, oc);

	k2 = dot_org - dot_org_ray * dot_org_ray;
	k1 = dot_org * ft_dot_product(oc, ray) - dot_org_oc * dot_org_ray;
	k0 = dot_org * ft_dot_product(oc, oc) - dot_org_oc * dot_org_oc - obj->s_cylinder.diameter * obj->s_cylinder.diameter * dot_org;

	double	h;
	h = k1 * k1 - k2 * k0;
	if (h < 0.0)
		return (INFINITY);
	h = sqrt(h);
	double	t;
	t = (-k1-h) / k2;

	double y;
	y = dot_org_oc + t * dot_org_ray;
	if (y > 0.0 && y < dot_org)
		return (t);
	return (INFINITY);
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
