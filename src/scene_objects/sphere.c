/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:46:50 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/05 16:08:23 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Initialize a sphere using the args as values
 *
 * @param type
 * @param args
 * @return int : -1 if error else 0
 */
int	create_sphere(t_scene_object *obj, int argc, char **args)
{
	if (argc < 4)
		return (rt_perror((char *)__func__, WRONG_ARGUMENT_COUNT), -1);
	obj->type = SPHERE;
	obj->shininess = 0.0;
	if (argc >= 5)
		obj->shininess = ft_atod(args[4]);
	obj->reflectiveness = 0.0;
	if (argc >= 6)
	{
		obj->reflectiveness = ft_atod(args[5]);
		if (obj->reflectiveness < 0.0 || obj->reflectiveness > 1.0)
			return (rt_perror((char *)__func__, REFL_OUT_OF_RANGE), -1);
	}
	obj->s_sphere.diameter = ft_atod(args[2]);
	if (obj->s_sphere.diameter < 0)
		return (rt_perror((char *)__func__, DIAMETER_OUT_OF_RANGE), -1);
	obj->color = atoc(args[3]);
	obj->s_sphere.sq_rad = obj->s_sphere.diameter * obj->s_sphere.diameter
		/ 4.0;
	obj->s_sphere.pos = atov(args[1]);
	if (!obj->s_sphere.pos)
		return (-1);
	return (0);
}

void	cleanup_sphere(t_scene_object *obj)
{
	if (!obj)
		return ;
	free(obj->s_sphere.pos);
}

double	intersect_sphere(t_vector3 *og, t_vector3 *ray, t_scene_object *obj,
	int (*is_valid)(double))
{
	double		coef[3];
	double		sol[2];
	t_vector3	*tmp;

	coef[0] = ft_dot_product(ray, ray);
	tmp = ft_v3_dir(og, obj->s_sphere.pos);
	coef[1] = 2.0 * ft_dot_product(ray, tmp);
	coef[2] = ft_dot_product(tmp, tmp)
		- obj->s_sphere.sq_rad;
	free(tmp);
	if (solve_quadratic(coef[0], coef[1], coef[2], sol) <= 0)
		return (INFINITY);
	sol[0] *= -1.0;
	sol[1] *= -1.0;
	if (!is_valid(sol[0]))
		sol[0] = INFINITY;
	if (!is_valid(sol[1]))
		sol[1] = INFINITY;
	return (closest_intersection(sol[0], sol[1], ray, og));
}

/**
 * @brief Allocat & computes the normal vector at the point on the sphere
 *
 * @param point
 * @return t_vector3*
 */
t_vector3	*normal_sphere(t_vector3 *og, t_vector3 *point, t_scene_object *obj)
{
	t_vector3	*normal;

	(void)og;
	normal = ft_v3_dir(obj->s_sphere.pos, point);
	if (!normal)
		return (NULL);
	ft_v3_innormalize(normal);
	return (normal);
}
