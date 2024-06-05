/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:50:58 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/05 15:33:08 by pgrossma         ###   ########.fr       */
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
	obj->s_cylinder.sq_rad = obj->s_cylinder.diameter * obj->s_cylinder.diameter
		/ 4.0;
	obj->s_cylinder.height = ft_atod(args[4]);
	if (obj->s_cylinder.height < 0)
		return (free(obj->s_cylinder.pos), free(obj->s_cylinder.dir),
			rt_perror((char *)__func__, HEIGHT_OUT_OF_RANGE), -1);
	obj->color = atoc(args[5]);
	return (0);
}

double	intersect_cylinder(t_vector3 *og, t_vector3 *ray, t_scene_object *obj,
		int (*is_valid)(double))
{
	double			distance_endcap;
	double			distance_side;
	t_is_cylinder	is_cylinder;

	is_cylinder.og = og;
	is_cylinder.ray = ray;
	is_cylinder.obj = obj;
	is_cylinder.obj_org_pos = ft_v3_sub(obj->s_cylinder.pos, og);
	distance_endcap = intersect_cylinder_endcaps(og, is_cylinder.obj_org_pos,
			ray, obj);
	distance_side = intersect_cylinder_side(&is_cylinder, is_valid);
	free(is_cylinder.obj_org_pos);
	return (closest_intersection(distance_endcap, distance_side, ray, og));
}

/**
 * @brief Allocat & computes the normal vector at the point on the cylinder
 *
 * @param point
 * @return t_vector3*
 */
t_vector3	*normal_cylinder(t_vector3 *og, t_vector3 *point,
		t_scene_object *obj)
{
	double	signed_distance;

	(void)og;
	signed_distance = signed_distance_t_cylinder_point(point,
			obj->s_cylinder.pos, obj);
	if (fabs(signed_distance) < EPSILON)
		return (ft_v3_mult(obj->s_cylinder.dir, -1));
	else if (fabs(signed_distance - obj->s_cylinder.height) < EPSILON)
		return (ft_v3_cpy(obj->s_cylinder.dir));
	else if (0 < signed_distance && signed_distance < obj->s_cylinder.height)
		return (normal_sides(signed_distance, point, obj));
	else
		return (ft_v3_cpy(&(t_vector3){0.000000, 0.0, 0.0}));
}

void	cleanup_cylinder(t_scene_object *obj)
{
	if (!obj)
		return ;
	free(obj->s_cylinder.pos);
	free(obj->s_cylinder.dir);
}
