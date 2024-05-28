/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:06:28 by pgrossma          #+#    #+#             */
/*   Updated: 2024/05/28 14:35:01 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	set_width_height(int32_t width, int32_t height)
{
	get_program()->canvas_width = width;
	get_program()->canvas_height = height;
	if (width > height)
	{
		get_program()->viewport_width = 1.0;
		get_program()->viewport_height = (double) height/width;
	}
	else
	{
		get_program()->viewport_width = (double) width/height;
		get_program()->viewport_height = 1.0;
	}
}

void	resize_hook(int32_t width, int32_t height, void *param)
{
	(void) param;

	set_width_height(width, height);
	mlx_resize_image(get_program()->image, width, height);
	update_viewport(get_object(CAMERA));
}
