/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:21:12 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/05 18:43:39 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	is_any_wrong(int *tmp)
{
	return (tmp[0] < 0 || tmp[0] > 255
			|| tmp[1] < 0 || tmp[1] > 255
			|| tmp[2] < 0 || tmp[2] > 255);
}

/**
 * @brief Converts R,G,B to uint32 storing 00RRGGBB
 *
 * @param arg
 * @return uint32_t
 */
uint32_t	atoc(char *arg)
{
	uint32_t	color;
	int			tmp[3];
	char		**splt;

	color = 0;
	splt = ft_split(arg, ',');
	if (!splt)
		return (set_error((char *)__func__, ALLOC), -1);
	if (!splt[0] || !splt[1] || !splt[2] || splt[3])
		return (rt_perror((char *)__func__, WRONG_ARGUMENT_COUNT), -1);
	tmp[0] = ft_btoi(splt[0], BASE10_STR);
	tmp[1] = ft_btoi(splt[1], BASE10_STR);
	tmp[2] = ft_btoi(splt[2], BASE10_STR);
	if (is_any_wrong(&tmp[0]))
		return (free_arr(splt, -1, 1), rt_perror((char *)__func__,
				COLOR_OUT_OF_RANGE), -1);
	color = (tmp[0] << 16) | (tmp[1] << 8) | tmp[2];
	return (free_arr(splt, -1, 1), color);
}

/**
 * @brief Converts X,Y,Z to Vector3(X, Y, Z)
 *
 * @param arg
 * @return uint32_t
 */
t_vector3	*atov(char *arg)
{
	t_vector3	*res;
	char		**splt;

	res = ft_v3_zero();
	if (!res)
		return (NULL);
	splt = ft_split(arg, ',');
	if (!splt)
		return (set_error((char *)__func__, ALLOC), NULL);
	if (!splt[0] || !splt[1] || !splt[2] || splt[3])
		return (rt_perror((char *)__func__, WRONG_ARGUMENT_COUNT), NULL);
	res->x = ft_atod(splt[0]);
	res->y = ft_atod(splt[1]);
	res->z = ft_atod(splt[2]);
	if (*get_errno() != NO_ERROR)
		return (free(res), NULL);
	return (free_arr(splt, -1, 1), res);
}
