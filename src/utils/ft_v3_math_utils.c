/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v3_math_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:58:36 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/25 12:28:21 by lgreau           ###   ########.fr       */
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

/**
 * @brief Computes & store the roation matrix rot from the given direction
 *
 * @param dir
 * @param up
 * @param rot
 */
void	ft_rotation_matrix(t_vector3 *dir, t_matrix *rot)
{
	t_vector3	*relative_up;
	t_vector3	*right;
	t_vector3	*real_up;

	dir->z *= -1;
	relative_up = ft_v3_zero();
	relative_up->y = 1.0;
	right = ft_v3_cross_product(relative_up, dir);
	ft_v3_innormalize(right);
	real_up = ft_v3_cross_product(dir, right);
	(*rot)[0][0] = right->x;
	(*rot)[0][1] = real_up->x;
	(*rot)[0][2] = -1.0 * dir->x;
	(*rot)[1][0] = right->y;
	(*rot)[1][1] = real_up->y;
	(*rot)[1][2] = -1.0 * dir->y;
	(*rot)[2][0] = right->z;
	(*rot)[2][1] = real_up->z;
	(*rot)[2][2] = -1.0 * dir->z;
	free(relative_up);
	free(right);
	free(real_up);
}
