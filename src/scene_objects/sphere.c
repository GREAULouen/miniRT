/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:46:50 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/24 17:39:03 by lgreau           ###   ########.fr       */
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
int	create_sphere(t_scene_object *obj, char **args)
{
	if (!args[1] || !args[2] || !args[3] || args[4])
		return (set_error((char *)__func__, INVALID_ARG), -1);
	obj->type = SPHERE;
	obj->s_sphere.pos = atov(args[1]);
	if (!obj->s_sphere.pos)
		return (-1);
	obj->s_sphere.diameter = ft_atod(args[2]);
	if (obj->s_sphere.diameter < 0)
		return (free(obj->s_sphere.pos),
			set_error((char *)__func__, INVALID_ARG), -1);
	obj->s_sphere.color = atoc(args[3]);
	return (0);
}

void	cleanup_sphere(t_scene_object *obj)
{
	if (!obj)
		return ;
	free(obj->s_sphere.pos);
}

double	intersect_sphere(t_vector3 *og, t_vector3 *ray, t_scene_object *obj)
{
	t_vector3	*res;
	double		a;
	double		b;
	double		c;
	double		delta;
	double		t1;
	double		t2;
	t_vector3	*tmp;

	res = ft_v3_zero();
	a = ft_dot_product(ray, ray);
	// print_v3("ray", ray, ONELINE);
	// print_v3("pos", obj->s_sphere.pos, ONELINE);
	tmp = ft_v3_dir(og, obj->s_sphere.pos);
	b = 2.0 * ft_dot_product(ray, tmp);
	c = ft_dot_product(tmp, tmp)
		- obj->s_sphere.diameter * obj->s_sphere.diameter / 4.0;
	ft_v3_inmult(tmp, 0);
	delta = b * b - 4.0 * a * c;
	// printf("a: %f, b: %f, c: %f, delta: %f\n", a, b, c, delta);
	if (delta < 0)
		return (free(res), free(tmp), INFINITY);
	t1 = -1.0 * (-1.0 * b + sqrt(delta)) / (2.0 * a);
	// if (t1 >= get_object(CAMERA)->s_camera.view_plane)
	// {
	// 	ft_v3_inadd(res, ray);
	// 	ft_v3_inmult(res, t1);
	// 	ft_v3_inadd(res, og);
	// }
	t2 = -1.0 * (-1.0 * b - sqrt(delta)) / (2.0 * a);
	if (fabs(t1) < fabs(t2))
		return (free(tmp), free(res), t1);
	return (free(tmp), free(res), t2);
	// if (t2 >= get_object(CAMERA)->s_camera.view_plane)
	// {
	// 	ft_v3_inadd(tmp, ray);
	// 	ft_v3_inmult(tmp, t2);
	// 	ft_v3_inadd(tmp, og);
	// }
	// printf("t1: %f, t2: %f\n", t1, t2);
	// if (ft_dot_product(res, res) == 0 && ft_dot_product(tmp, tmp) == 0)
	// 	return (free(res), free(tmp), INFINITY);
	// if (ft_dot_product(res, res) != 0 && ft_dot_product(tmp, tmp) == 0)
	// 	return (free(tmp), free(res), t1);
	// if (ft_dot_product(res, res) == 0 && ft_dot_product(tmp, tmp) != 0)
	// 	return (free(res), free(tmp), t2);
	// if (ft_dot_product(res, res) != 0 && ft_dot_product(tmp, tmp) != 0
	// 		&& ft_dot_product(og, res) > ft_dot_product(og, tmp))
	// 	return (free(res), free(tmp), t2);
	// return (free(tmp), free(res), t1);
}

/**
 * @brief Allocat & computes the normal vector at the point on the sphere
 *
 * @param point
 * @return t_vector3*
 */
t_vector3	*normal_sphere(t_vector3 *point, t_scene_object *obj)
{
	t_vector3	*normal;

	normal = ft_v3_sub(point, obj->s_sphere.pos);
	if (!normal)
		return (NULL);
	return (normal);
}
