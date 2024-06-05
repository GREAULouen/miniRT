/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dot_product.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:37:47 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/14 11:42:43 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector3.h"

double	ft_dot_product(t_vector3 *v1, t_vector3 *v2)
{
	if (!v1 || !v2)
		return (set_error((char *)__func__, INVALID_ARG), -1);
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}
