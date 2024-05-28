/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v3_math_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:58:36 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/28 11:35:45 by lgreau           ###   ########.fr       */
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
	t_vector3	n_dir;
	t_vector3	og;
	t_vector3	*axis;
	float		cosA;
	float		k;

	n_dir = (t_vector3){dir->x, dir->y, -dir->z};
	og = (t_vector3){0.0, 0.0, -1.0};
	axis = ft_v3_cross_product(&n_dir, &og);
	cosA = ft_dot_product(&n_dir, &og);
	k = 1.0 / (1.0 + cosA);

	(*rot)[0][0] = (axis->x * axis->x * k) + cosA;
	(*rot)[0][1] = (axis->y * axis->x * k) - axis->z;
	(*rot)[0][2] = (axis->z * axis->x * k) + axis->y;
	(*rot)[1][0] = (axis->x * axis->y * k) + axis->z;
	(*rot)[1][1] = (axis->y * axis->y * k) + cosA;
	(*rot)[1][2] = (axis->z * axis->y * k) - axis->x;
	(*rot)[2][0] = (axis->x * axis->z * k) - axis->y;
	(*rot)[2][1] = (axis->y * axis->z * k) + axis->x;
	(*rot)[2][2] = (axis->z * axis->z * k) + cosA;

	for(int row = 0; row < 3; row++)
	{
		for(int col = 0; col < 3; col++)
			printf("% .6f ", (*rot)[row][col]);
		printf("\n");
	}
	free(axis);
}

/**
 * @brief Rotates the ray to match the direction of the camera
 *
 * @param ray
 */
void	ft_apply_rotate(t_vector3 *dir, t_matrix *rot, t_vector3 *res)
{
	res->x = dir->x * (*rot)[0][0] + dir->y * (*rot)[0][1] + dir->z * (*rot)[0][2];
	res->y = dir->x * (*rot)[1][0] + dir->y * (*rot)[1][1] + dir->z * (*rot)[1][2];
	res->z = dir->x * (*rot)[2][0] + dir->y * (*rot)[2][1] + dir->z * (*rot)[2][2];
}
