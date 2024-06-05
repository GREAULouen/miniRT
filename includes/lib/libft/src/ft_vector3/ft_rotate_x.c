/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:58:14 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/25 14:26:15 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector3.h"

/**
 * @brief In place rotation of v around X axis for theta radians (clockwise)
 *
 * @param v
 * @param theta
 */
void	ft_inrotate_x(t_vector3 *v, double theta)
{
	double	og_y;
	double	og_z;

	og_y = -1.0 * v->y;
	og_z = v->z;
	v->y = cos(theta) * og_y - sin(theta) * og_z;
	v->z = sin(theta) * og_y + cos(theta) * og_z;
}
