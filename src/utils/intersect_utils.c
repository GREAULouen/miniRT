/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:50:18 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/05 16:10:15 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Computes the point of intersection between the ray and
 * the scene object from the solution to it's intersection equation found
 *
 * @param intersect
 * @param ray
 * @param obj
 * @return t_vector3*
 */
t_vector3	*sol_to_point(double intersect, t_vector3 *ray, t_vector3 *og)
{
	t_vector3	tmp;

	tmp = (t_vector3){ray->x, ray->y, ray->z};
	ft_v3_inmult(&tmp, intersect);
	ft_v3_inadd(&tmp, og);
	return (ft_v3_cpy(&tmp));
}

/**
 * @brief Returns the closest solution to the origin of the ray
 *
 * @param t1
 * @param t2
 * @param ray
 * @param og
 * @return double
 */
double	closest_intersection(double t1, double t2, t_vector3 *ray,
	t_vector3 *og)
{
	t_vector3	*ogt1;
	t_vector3	*ogt2;

	if (t1 == INFINITY && t2 == INFINITY)
		return (INFINITY);
	if (t1 == INFINITY && t2 != INFINITY)
		return (t2);
	if (t1 != INFINITY && t2 == INFINITY)
		return (t1);
	ogt1 = sol_to_point(t1, ray, og);
	ft_v3_insub(ogt1, og);
	ogt2 = sol_to_point(t2, ray, og);
	ft_v3_insub(ogt2, og);
	if (ft_dot_product(ogt1, ogt1) > ft_dot_product(ogt2, ogt2))
		return (free(ogt1), free(ogt2), t2);
	return (free(ogt1), free(ogt2), t1);
}

int	valid_sol_from_cam(double sol)
{
	return (sol >= get_object(CAMERA)->s_camera.view_plane);
}

int	valid_sol_till_spot(double sol)
{
	return (sol >= EPSILON && sol <= (1 - EPSILON));
}

int	is_in_plane(double sol, t_vector3 *ray, t_vector3 *og, t_scene_object *obj)
{
	t_vector3	*pos;
	t_vector3	u;
	t_vector3	*v;
	t_vector3	*to_pos;

	pos = sol_to_point(sol, ray, og);
	if (fabs(obj->s_plane.normal->x) > fabs(obj->s_plane.normal->y))
		u = (t_vector3){-obj->s_plane.normal->z, 0.0, obj->s_plane.normal->x};
	else
		u = (t_vector3){0.0, obj->s_plane.normal->z, -obj->s_plane.normal->y};
	v = ft_v3_cross_product(&u, obj->s_plane.normal);
	ft_v3_innormalize(&u);
	ft_v3_innormalize(v);
	to_pos = ft_v3_dir(obj->s_plane.pos, pos);
	if (fabs(ft_dot_product(to_pos, &u)) > obj->s_plane.width / 2.0
		|| fabs(ft_dot_product(to_pos, v)) > obj->s_plane.height / 2.0)
		return (free(v), free(to_pos), free(pos), 0);
	return (free(v), free(to_pos), free(pos), 1);
}
