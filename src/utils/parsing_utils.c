/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:21:12 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/14 18:33:27 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Converts R,G,B to uint32 storing 00RRGGBB
 *
 * @param arg
 * @return uint32_t
 */
uint32_t	atoc(char *arg)
{
	uint32_t	color;
	int			tmp;
	char		**splt;

	color = 0;
	splt = ft_split(arg, ',');
	if (!splt)
		return (set_error((char *)__func__, ALLOC), -1);
	if (!splt[0] || !splt[1] || !splt[2] || splt[3])
		return (set_error((char *)__func__, INVALID_ARG), -1);
	tmp = ft_btoi(splt[0], BASE10_STR);
	if (*get_errno() != NO_ERROR || tmp < 0 || tmp >= 256)
		return (set_error((char *)__func__, INVALID_ARG), 0);
	color |= (tmp << SHIFT_R);
	tmp = ft_btoi(splt[1], BASE10_STR);
	if (*get_errno() != NO_ERROR || tmp < 0 || tmp >= 256)
		return (set_error((char *)__func__, INVALID_ARG), 0);
	color |= (tmp << SHIFT_G);
	tmp = ft_btoi(splt[2], BASE10_STR);
	if (*get_errno() != NO_ERROR || tmp < 0 || tmp >= 256)
		return (set_error((char *)__func__, INVALID_ARG), 0);
	color |= tmp;
	return (color);
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
		return (set_error((char *)__func__, INVALID_ARG), NULL);
	res->x = ft_atod(splt[0]);
	res->y = ft_atod(splt[1]);
	res->z = ft_atod(splt[2]);
	if (*get_errno() != NO_ERROR)
		return (free(res), NULL);
	return (res);
}