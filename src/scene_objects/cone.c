/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:28:57 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/03 15:05:21 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	create_cone(t_scene_object *obj, int argc, char **args)
{
	if (argc < 6)
		return (rt_perror((char *)__func__, WRONG_ARGUMENT_COUNT), -1);
	obj->type = CONE;
	obj->s_cone.diameter = ft_atod(args[3]);
	if (obj->s_cone.diameter < 0.0)
		return (rt_perror((char *)__func__, DIAMETER_OUT_OF_RANGE), -1);
	obj->s_cone.height = ft_atod(args[4]);
	if (obj->s_cone.height < 0.0)
		return (rt_perror((char *)__func__, HEIGHT_OUT_OF_RANGE), -1);
	obj->s_cone.tan_theta = obj->s_cone.diameter / (2.0 * obj->s_cone.height);
	obj->s_cone.sq_tan_theta = pow(obj->s_cone.tan_theta, 2.0);
	obj->color = atoc(args[5]);
	obj->shininess = 0.0;
	if (argc >= 7)
		obj->shininess = ft_atod(args[6]);
	obj->reflectiveness = 0.0;
	if (argc >= 8)
		obj->reflectiveness = ft_atod(args[7]);
	obj->s_cone.pos = atov(args[1]);
	if (!obj->s_cone.pos)
		return (-1);
	obj->s_cone.dir = atov(args[2]);
	if (!obj->s_cone.dir)
		return (free(obj->s_cone.pos), -1);
	ft_v3_innormalize(obj->s_cone.dir);
	ft_rotation_matrix(obj->s_cone.dir, &obj->s_cone.rot);
	ft_invert_rot_matrix(&obj->s_cone.rot, &obj->s_cone.inv_rot);
	return (0);
}

void	cleanup_cone(t_scene_object *obj)
{
	if (!obj)
		return ;
	free(obj->s_cone.pos);
	free(obj->s_cone.dir);
}

double	intersect_cone(t_vector3 *og, t_vector3 *ray, t_scene_object *obj, int (*is_valid)(double))
{
	t_vector3	n_og;
	t_vector3	n_ray;
	double		coef[3];
	double		sol[2];
	t_vector3	*tmp;

	ft_apply_rotate(&(t_vector3){og->x - obj->s_cone.pos->x, og->y - obj->s_cone.pos->y, og->z - obj->s_cone.pos->z}, &obj->s_cone.inv_rot, &n_og);
	ft_apply_rotate(ray, &obj->s_cone.inv_rot, &n_ray);
	coef[0] = pow(n_ray.x, 2.0) + pow(n_ray.y, 2.0) - pow(n_ray.z, 2.0) * obj->s_cone.sq_tan_theta;
	coef[1] = 2.0 * (n_og.x * n_ray.x + n_og.y * n_ray.y - n_og.z * n_ray.z * obj->s_cone.sq_tan_theta);
	coef[2] = pow(n_og.x, 2.0) + pow(n_og.y, 2.0) - pow(n_og.z, 2.0) * obj->s_cone.sq_tan_theta;
	if (solve_quadratic(coef[0], coef[1], coef[2], sol) <= 0)
		return (INFINITY);
	tmp = sol_to_point(sol[0], &n_ray, &n_og);
	if (!is_valid(sol[0]) || tmp->z > 0 || fabs(tmp->z) > obj->s_cone.height)
		sol[0] = INFINITY;
	free(tmp);
	tmp = sol_to_point(sol[1], &n_ray, &n_og);
	if (!is_valid(sol[1]) || tmp->z > 0 || fabs(tmp->z) > obj->s_cone.height)
		sol[1] = INFINITY;
	free(tmp);
	return (closest_intersection(sol[0], sol[1], ray, og));
}

t_vector3	*normal_cone(t_vector3 *og, t_vector3 *point, t_scene_object *obj)
{
	t_vector3	*normal;
	t_vector3	local_normal;
	t_vector3	tmp;

	(void)og;
	// tmp = (t_vector3){2.0 * point->x, 2.0 * point->y, -2.0 * point->z * obj->s_cone.sq_tan_theta};
	// ft_v3_innormalize(&tmp);
	// normal = ft_v3_zero();
	// ft_apply_rotate(&tmp, &obj->s_cone.rot, normal);
	tmp = (t_vector3){0.0, 0.0, 0.0};
	ft_apply_rotate(&(t_vector3){point->x - obj->s_cone.pos->x, point->y - obj->s_cone.pos->y, point->z - obj->s_cone.pos->z}, &obj->s_cone.rot, &tmp);
	local_normal = (t_vector3){2.0 * tmp.x, 2.0 * tmp.y, -2.0 * tmp.z * obj->s_cone.sq_tan_theta};
	ft_v3_innormalize(&local_normal);
	normal = ft_v3_zero();
	ft_apply_rotate(&local_normal, &obj->s_cone.inv_rot, normal);
	ft_v3_innormalize(normal);
	return (normal);
}
