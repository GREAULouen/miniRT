/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v3_inop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:02:24 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/16 14:05:04 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector3.h"

/**
 * @brief Modifies v1 to be v1 + v2
 *
 * @param v1
 * @param v2
 * @return t_vector3*
 */
void	ft_v3_inadd(t_vector3 *v1, t_vector3 *v2)
{
	if (!v1 || !v2)
		return (set_error((char *)__func__, INVALID_ARG));
	v1->x += v2->x;
	v1->y += v2->y;
	v1->z += v2->z;
}

/**
 * @brief Modifies v1 to be v1 - v2
 *
 * @param v1
 * @param v2
 * @return t_vector3*
 */
void	ft_v3_insub(t_vector3 *v1, t_vector3 *v2)
{
	if (!v1 || !v2)
		return (set_error((char *)__func__, INVALID_ARG));
	v1->x -= v2->x;
	v1->y -= v2->y;
	v1->z -= v2->z;
}

/**
 * @brief Modifies v1 to be v1 * coef
 *
 * @param v1
 * @param v2
 * @return t_vector3*
 */
void	ft_v3_inmult(t_vector3 *v1, double coef)
{
	if (!v1)
		return (set_error((char *)__func__, INVALID_ARG));
	v1->x *= coef;
	v1->y *= coef;
	v1->z *= coef;
}

/**
 * @brief Modifies v1 to be v1 / coef
 *
 * @param v1
 * @param v2
 * @return t_vector3*
 */
void	ft_v3_indiv(t_vector3 *v1, double coef)
{
	if (!v1 || coef == 0)
		return (set_error((char *)__func__, INVALID_ARG));
	v1->x /= coef;
	v1->y /= coef;
	v1->z /= coef;
}
