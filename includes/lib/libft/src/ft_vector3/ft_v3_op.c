/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v3_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:55:24 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/14 13:04:12 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector3.h"

/**
 * @brief Allocates & returns the vector v1 + v2
 *
 * @param v1
 * @param v2
 * @return t_vector3*
 */
t_vector3	*ft_v3_add(t_vector3 *v1, t_vector3 *v2)
{
	t_vector3	*res;

	if (!v1 || !v2)
		return (set_error((char *)__func__, INVALID_ARG), NULL);
	res = malloc(sizeof(t_vector3));
	if (!res)
		return (set_error((char *)__func__, ALLOC), NULL);
	res->x = v1->x + v2->x;
	res->y = v1->y + v2->y;
	res->z = v1->z + v2->z;
	return (res);
}

/**
 * @brief Allocates & returns the vector v1 - v2
 *
 * @param v1
 * @param v2
 * @return t_vector3*
 */
t_vector3	*ft_v3_sub(t_vector3 *v1, t_vector3 *v2)
{
	t_vector3	*res;

	if (!v1 || !v2)
		return (set_error((char *)__func__, INVALID_ARG), NULL);
	res = malloc(sizeof(t_vector3));
	if (!res)
		return (set_error((char *)__func__, ALLOC), NULL);
	res->x = v1->x - v2->x;
	res->y = v1->y - v2->y;
	res->z = v1->z - v2->z;
	return (res);
}

/**
 * @brief Allocates & returns the vector coef * v1
 *
 * @param v1
 * @param v2
 * @return t_vector3*
 */
t_vector3	*ft_v3_mult(t_vector3 *v1, double coef)
{
	t_vector3	*res;

	if (!v1)
		return (set_error((char *)__func__, INVALID_ARG), NULL);
	res = malloc(sizeof(t_vector3));
	if (!res)
		return (set_error((char *)__func__, ALLOC), NULL);
	res->x = v1->x * coef;
	res->y = v1->y * coef;
	res->z = v1->z * coef;
	return (res);
}

/**
 * @brief Allocates & returns the vector v1 / coef
 *
 * @param v1
 * @param v2
 * @return t_vector3*
 */
t_vector3	*ft_v3_div(t_vector3 *v1, double coef)
{
	t_vector3	*res;

	if (!v1 || coef == 0)
		return (set_error((char *)__func__, INVALID_ARG), NULL);
	res = malloc(sizeof(t_vector3));
	if (!res)
		return (set_error((char *)__func__, ALLOC), NULL);
	res->x = v1->x / coef;
	res->y = v1->y / coef;
	res->z = v1->z / coef;
	return (res);
}
