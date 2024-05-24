/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:50:18 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/24 12:04:51 by lgreau           ###   ########.fr       */
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
t_vector3	*sol_to_point(double intersect, t_vector3 *ray)
{
	t_vector3	*res;

	res = ft_v3_cpy(ray);
	ft_v3_inmult(res, intersect);
	ft_v3_inadd(res, get_object(CAMERA)->s_camera.pos);
	return (res);
}
