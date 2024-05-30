/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v3_math_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:58:36 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/30 17:06:51 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Computes & returns the length of a t_vector3 object
 *
 * @param v
 * @return double
 */
double	ft_v3_length(t_vector3 *v)
{
	if (!v)
		return (set_error((char *)__func__, INVALID_ARG), 0);
	return (sqrt(ft_dot_product(v, v)));
}

/**
 * @brief Allocates & returns the vector v1 x v2
 *
 * @param v1
 * @param v2
 * @return t_vector3*
 */
t_vector3	*ft_v3_cross_product(t_vector3 *v1, t_vector3 *v2)
{
	t_vector3	*res;

	res = ft_v3_zero();
	res->x = v1->y * v2->z - v1->z * v2->y;
	res->y = v1->z * v2->x - v1->x * v2->z;
	res->z = v1->x * v2->y - v1->y * v2->x;
	return (res);
}

/**
 * @brief In place normalizaion of v
 *
 * @param v
 */
void	ft_v3_innormalize(t_vector3 *v)
{
	double	v_len;

	v_len = ft_v3_length(v);
	if (v_len <= EPSILON)
		return ;
	v->x /= v_len;
	v->y /= v_len;
	v->z /= v_len;
}
