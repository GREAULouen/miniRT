/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:06:28 by pgrossma          #+#    #+#             */
/*   Updated: 2024/06/05 16:12:53 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	set_width_height(int32_t width, int32_t height)
{
	t_program	*program;

	program = get_program();
	program->canvas_width = width;
	program->canvas_height = height;
	if (width > height)
	{
		program->viewport_width = 1.0;
		program->viewport_height = (double) height / width;
	}
	else
	{
		program->viewport_width = (double) width / height;
		program->viewport_height = 1.0;
	}
	program->half_view_width = program->viewport_width / 2.0;
	program->half_view_height = program->viewport_height / 2.0;
	program->vc_width_ratio = program->viewport_width / width;
	program->vc_height_ratio = program->viewport_height / height;
}

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_program	*program;

	program = get_program();
	(void) param;
	set_width_height(width, height);
	mlx_resize_image(program->image, width, height);
	update_viewport(get_object(CAMERA));
	free(program->avg_buffer);
	program->avg_buffer = ft_calloc(program->canvas_width
			* program->canvas_height, sizeof(t_vector3));
	if (!program->avg_buffer)
		return ;
	program->image_count = 0;
}
