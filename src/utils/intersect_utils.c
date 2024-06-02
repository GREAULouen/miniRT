/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:50:18 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/02 13:25:58 by lgreau           ###   ########.fr       */
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
