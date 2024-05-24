/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v3_math_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:58:36 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/24 12:02:14 by lgreau           ###   ########.fr       */
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
