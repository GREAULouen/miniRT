/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_y.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:06:17 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/16 14:14:57 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector3.h"

/**
 * @brief In place rotation of v around Y axis for theta radians (clockwise)
 *
 * @param v
 * @param theta
 */
void	ft_inrotate_y(t_vector3 *v, double theta)
{
	double	og_x;
	double	og_z;

	og_x = v->x;
	og_z = v->z;
	v->x = cos(theta) * og_x + sin(theta) * og_z;
	v->z = -1 * sin(theta) * og_x + cos(theta) * og_z;
}
