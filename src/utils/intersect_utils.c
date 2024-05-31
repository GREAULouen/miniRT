/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:50:18 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/31 11:10:27 by lgreau           ###   ########.fr       */
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
t_vector3	*sol_to_point(double intersect, t_vector3 *ray, t_vector3 *og, t_scene_object *obj)
{
	t_vector3	tmp;
	t_vector3	*res;

	tmp = (t_vector3){ray->x, ray->y, ray->z};
	ft_v3_inmult(&tmp, intersect);
	ft_v3_inadd(&tmp, og);
	if (!obj || obj->type != CONE)
		return (ft_v3_cpy(&tmp));
	res = ft_v3_zero();
	ft_apply_rotate(&tmp, &obj->s_cone.rot, res);
	ft_v3_inadd(res, obj->s_cone.pos);
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
	ogt1 = sol_to_point(t1, ray, og, NULL);
	ft_v3_insub(ogt1, og);
	ogt2 = sol_to_point(t2, ray, og, NULL);
	ft_v3_insub(ogt2, og);
	// if (ray->x < 0.03 && ray->x > -0.03 & ray->z < 0.03 && ray->z > -0.03)
	// {
	// 	print_v3("  |- og_t1", ogt1, ONELINE);
	// 	print_v3("  |- og_t2", ogt2, ONELINE);
	// 	printf("  |- dot t1 : %f\n", ft_dot_product(ogt1, ogt1));
	// 	printf("  |- dot t2 : %f\n", ft_dot_product(ogt2, ogt2));
	// }
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
