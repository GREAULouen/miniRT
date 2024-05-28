/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:46:50 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/28 15:37:40 by lgreau           ###   ########.fr       */
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
	if (argc < 4 || !args[1] || !args[2] || !args[3])
		return (set_error((char *)__func__, INVALID_ARG), -1);
	obj->type = SPHERE;
	obj->s_sphere.pos = atov(args[1]);
	if (!obj->s_sphere.pos)
		return (-1);
	obj->s_sphere.diameter = ft_atod(args[2]);
	if (obj->s_sphere.diameter < 0)
		return (free(obj->s_sphere.pos),
			set_error((char *)__func__, INVALID_ARG), -1);
	obj->color = atoc(args[3]);
	obj->s_sphere.sq_rad = obj->s_sphere.diameter * obj->s_sphere.diameter / 4.0;
	obj->shininess = 0.0;
	if (args[4])
		obj->shininess = ft_atod(args[4]);
	return (0);
}

void	cleanup_sphere(t_scene_object *obj)
{
	if (!obj)
		return ;
	free(obj->s_sphere.pos);
}

double	intersect_sphere(t_vector3 *og, t_vector3 *ray, t_scene_object *obj, int (*is_valid)(double))
{
	double		a;
	double		b;
	double		c;
	double		delta;
	double		t1;
	double		t2;
	t_vector3	*tmp;

	a = ft_dot_product(ray, ray);
	tmp = ft_v3_dir(og, obj->s_sphere.pos);
	b = 2.0 * ft_dot_product(ray, tmp);
	c = ft_dot_product(tmp, tmp)
		- obj->s_sphere.sq_rad;
	free(tmp);
	delta = b * b - 4.0 * a * c;
	if (delta < 0)
		return (INFINITY);
	t1 = -1.0 * (-1.0 * b + sqrt(delta)) / (2.0 * a);
	if (!is_valid(t1))
		t1 = INFINITY;
	t2 = -1.0 * (-1.0 * b - sqrt(delta)) / (2.0 * a);
	if (!is_valid(t2))
		t2 = INFINITY;
	return (closest_intersection(t1, t2, ray, og));
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
