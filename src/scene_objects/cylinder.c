/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:50:58 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/30 18:16:45 by pgrossma         ###   ########.fr       */
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
	double		a;
	double		b;
	double		c;
	double		delta;
	double		t1;
	double		t2;
	t_matrix	*rot_ray = malloc(sizeof(t_matrix));
	t_vector3	rotated_ray;

	og = ft_v3_sub(og, obj->s_cylinder.pos);
	ft_rotation_matrix(ray, rot_ray);
	ft_apply_rotate(ray, rot_ray, &rotated_ray);
	ft_rotation_matrix(og, rot_ray);
	ft_apply_rotate(og, rot_ray, og);
	a = rotated_ray.x * rotated_ray.x + rotated_ray.y * rotated_ray.y;
	b = 2.0 * ft_dot_product(&rotated_ray, og);
	c = ft_dot_product(&rotated_ray, &rotated_ray)
		- obj->s_cylinder.sq_rad;
	free(og);
	delta = b * b - 4.0 * a * c;
	if (delta < 0)
		return (INFINITY);
	t1 = -1.0 * (-1.0 * b + sqrt(delta)) / (2.0 * a);
	if (!is_valid(t1))
		t1 = INFINITY;
	t2 = -1.0 * (-1.0 * b - sqrt(delta)) / (2.0 * a);
	if (!is_valid(t2))
		t2 = INFINITY;
	// if (ray->x < 0.03 && ray->x > -0.03 & ray->z < 0.03 && ray->z > -0.03)
	// {
	// 	print_v3("ray", ray, ONELINE);
	// 	printf("  |-a: %f\n", a);
	// 	printf("  |-b: %f\n", b);
	// 	printf("  |-c: %f\n", c);
	// 	printf("  |- delta: %f\n", delta);
	// 	printf("  |- t1: %f\n", t1);
	// 	printf("  |- t2: %f\n", t2);
	// }
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
