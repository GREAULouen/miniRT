/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:28:57 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/05 15:59:56 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	additional_args(t_scene_object *obj, int argc, char **args)
{
	obj->s_cone.tan_theta = obj->s_cone.diameter / (2.0 * obj->s_cone.height);
	obj->s_cone.sq_tan_theta = pow(obj->s_cone.tan_theta, 2.0);
	obj->shininess = 0.0;
	if (argc >= 7)
		obj->shininess = ft_atod(args[6]);
	obj->reflectiveness = 0.0;
	if (argc >= 8)
	{
		obj->reflectiveness = ft_atod(args[7]);
		if (obj->reflectiveness < 0.0 || obj->reflectiveness > 1.0)
			return (rt_perror((char *)__func__, REFL_OUT_OF_RANGE), -1);
	}
	return (0);
}

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
	obj->color = atoc(args[5]);
	if (obj->color == (uint32_t)-1 || additional_args(obj, argc, args) < 0)
		return (-1);
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

double	intersect_cone(t_vector3 *og, t_vector3 *ray, t_scene_object *obj,
	int (*is_valid)(double))
{
	t_vector3	*nv;
	double		coef[3];
	double		sol[2];
	t_vector3	*tmp[3];

	nv = (t_vector3[2]){(t_vector3){0.0, 0.0, 0.0}, (t_vector3){0.0, 0.0, 0.0}};
	tmp[0] = ft_v3_dir(obj->s_cone.pos, og);
	ft_apply_rotate(tmp[0], &obj->s_cone.inv_rot, &nv[1]);
	ft_apply_rotate(ray, &obj->s_cone.inv_rot, &nv[0]);
	coef[0] = pow(nv[0].x, 2.0) + pow(nv[0].y, 2.0) - pow(nv[0].z, 2.0)
		* obj->s_cone.sq_tan_theta;
	coef[1] = 2.0 * (nv[1].x * nv[0].x + nv[1].y * nv[0].y - nv[1].z * nv[0].z
			* obj->s_cone.sq_tan_theta);
	coef[2] = pow(nv[1].x, 2.0) + pow(nv[1].y, 2.0) - pow(nv[1].z, 2.0)
		* obj->s_cone.sq_tan_theta;
	if (solve_quadratic(coef[0], coef[1], coef[2], sol) <= 0)
		return (free(tmp[0]), INFINITY);
	tmp[1] = sol_to_point(sol[0], &nv[0], &nv[1]);
	if (!is_valid(sol[0]) || tmp[1]->z > 0 || tmp[1]->z > obj->s_cone.height)
		sol[0] = INFINITY;
	tmp[2] = sol_to_point(sol[1], &nv[0], &nv[1]);
	if (!is_valid(sol[1]) || tmp[2]->z > 0 || tmp[2]->z > obj->s_cone.height)
		sol[1] = INFINITY;
	return (free(tmp[0]), free(tmp[1]), free(tmp[2]),
		closest_intersection(sol[0], sol[1], ray, og));
}

t_vector3	*normal_cone(t_vector3 *og, t_vector3 *point, t_scene_object *obj)
{
	t_vector3	*normal;
	t_vector3	local_normal;
	t_vector3	tmp;

	(void)og;
	tmp = (t_vector3){0.0, 0.0, 0.0};
	ft_apply_rotate(&(t_vector3){point->x - obj->s_cone.pos->x, point->y
		- obj->s_cone.pos->y, point->z - obj->s_cone.pos->z},
		&obj->s_cone.rot, &tmp);
	local_normal = (t_vector3){2.0 * tmp.x, 2.0 * tmp.y, -2.0 * tmp.z
		* obj->s_cone.sq_tan_theta};
	ft_v3_innormalize(&local_normal);
	normal = ft_v3_zero();
	ft_apply_rotate(&local_normal, &obj->s_cone.inv_rot, normal);
	ft_v3_innormalize(normal);
	return (normal);
}
