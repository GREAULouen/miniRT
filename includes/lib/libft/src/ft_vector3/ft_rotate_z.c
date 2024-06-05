/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_z.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:08:07 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/16 14:14:52 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector3.h"

/**
 * @brief In place rotation of v around Z axis for theta radians (clockwise)
 *
 * @param v
 * @param theta
 */
void	ft_inrotate_z(t_vector3 *v, double theta)
{
	double	og_x;
	double	og_y;

	og_x = v->x;
	og_y = v->y;
	v->x = cos(theta) * og_x - sin(theta) * og_y;
	v->y = sin(theta) * og_x + cos(theta) * og_y;
}
