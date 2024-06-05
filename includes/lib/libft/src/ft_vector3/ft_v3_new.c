/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v3_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:11:24 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/21 12:18:52 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector3.h"

/**
 * @brief Allocates & returns the vector (0, 0, 0)
 *
 * @return t_vector3*
 */
t_vector3	*ft_v3_zero(void)
{
	t_vector3	*res;

	res = malloc(sizeof(t_vector3));
	if (!res)
		return (set_error((char *)__func__, ALLOC), NULL);
	res->x = 0;
	res->y = 0;
	res->z = 0;
	return (res);
}

/**
 * @brief Allocates & returns the vector (x, y, z)
 *
 * @return t_vector3*
 */
t_vector3	*ft_v3_new(double x, double y, double z)
{
	t_vector3	*res;

	res = malloc(sizeof(t_vector3));
	if (!res)
		return (set_error((char *)__func__, ALLOC), NULL);
	res->x = x;
	res->y = y;
	res->z = z;
	return (res);
}

/**
 * @brief Allocates & returns the vector (x, y, z)
 *
 * @return t_vector3*
 */
t_vector3	*ft_v3_cpy(t_vector3 *v)
{
	t_vector3	*res;

	res = malloc(sizeof(t_vector3));
	if (!res)
		return (set_error((char *)__func__, ALLOC), NULL);
	res->x = v->x;
	res->y = v->y;
	res->z = v->z;
	return (res);
}

/**
 * @brief Allocates & returns the new vector v1v2 (from v1 to v2)
 *
 * @param v1
 * @param v2
 * @return t_vector3* Not normalized
 */
t_vector3	*ft_v3_dir(t_vector3 *v1, t_vector3 *v2)
{
	t_vector3	*res;

	res = malloc(sizeof(t_vector3));
	if (!res)
		return (set_error((char *)__func__, ALLOC), NULL);
	res->x = v2->x - v1->x;
	res->y = v2->y - v1->y;
	res->z = v2->z - v1->z;
	return (res);
}
