/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:06:35 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/03 13:53:45 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	minus_one_rot_matrix(t_matrix *rot)
{
	int	row;
	int	col;

	row = -1;
	while (++row < 3)
	{
		col = -1;
		while (++col < 3)
			(*rot)[row][col] = (row == col) * (1.0 - 2.0 * (row == 2));
	}
	for(int row = 0; row < 3; row++)
	{
		for(int col = 0; col < 3; col++)
			printf("% .6f ", (*rot)[row][col]);
		printf("\n");
	}
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

	if (dir->x == 0.0 && dir->y == 0.0 && dir->z == -1.0)
		return(minus_one_rot_matrix(rot));
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
 * @brief Stores the invert of og rot matrix in inv
 *
 * @param og
 * @param inv
 */
void	ft_invert_rot_matrix(t_matrix *og, t_matrix *inv)
{
	int	row;
	int	col;

	row = -1;
	while (++row < 3)
	{
		col = -1;
		while (++col < 3)
			(*inv)[row][col] = (*og)[col][row];
	}
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
