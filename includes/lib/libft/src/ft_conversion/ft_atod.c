/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:42:02 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/05 15:45:24 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_conversion.h"

/**
 * @brief Returns 10^n
 *
 * @param n
 * @return int
 */
static int	ft_pow10(int n)
{
	if (n == 0)
		return (1);
	return (10 * ft_pow10(n - 1));
}

/**
 * @brief Converts a string to a double
 *
 * @param arg
 * @return float
 */
double	ft_atod(char *arg)
{
	double	res;
	int		index;
	int		dot_place;

	if (!arg || !arg[0] || arg[0] == '.')
		return (set_error((char *)__func__, INVALID_ARG), 0);
	if (arg[0] == '-')
		return (-1 * ft_atod(&arg[1]));
	index = -1;
	dot_place = -1;
	res = 0;
	while (arg[++index])
	{
		if (arg[index] == '.')
			dot_place = index;
		else
			res = res * 10 + (arg[index] - '0');
	}
	if (dot_place < 0)
		return (res);
	return (res / ft_pow10(ft_strlen(arg) - 1 - dot_place));
}
