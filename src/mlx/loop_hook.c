/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:58:46 by pgrossma          #+#    #+#             */
/*   Updated: 2024/05/28 14:58:52 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	loop_hook(void *param)
{
	(void) param;
	init_ray();
	// get_object(CAMERA)->s_camera.pos->y += 1.0;
}