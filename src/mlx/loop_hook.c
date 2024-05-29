/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:58:46 by pgrossma          #+#    #+#             */
/*   Updated: 2024/05/28 15:29:23 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	loop_hook(void *param)
{
	(void) param;
	init_ray();
	ft_v3_inadd(get_object(SPHERE)->s_sphere.pos, &(t_vector3){1.0, 1.0, 1.0});
	// get_object(CAMERA)->s_camera.pos->y += 1.0;
	// ft_inrotate_x(get_object(CAMERA)->s_camera.dir, 0.1);
	// ft_rotation_matrix(get_object(CAMERA)->s_camera.dir, &get_object(CAMERA)->s_camera.rot);
}
