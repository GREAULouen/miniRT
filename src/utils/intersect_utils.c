/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:50:18 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/24 19:25:14 by lgreau           ###   ########.fr       */
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
	t_vector3	*res;

	res = ft_v3_cpy(ray);
	ft_v3_inmult(res, intersect);
	ft_v3_inadd(res, og);
	return (res);
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
double	closest_intersection(double t1, double t2, t_vector3 *ray, t_vector3 *og)
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
	ogt2 = sol_to_point(t2, ray, og);
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
