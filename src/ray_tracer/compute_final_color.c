/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_final_color.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 15:25:37 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/02 16:37:39 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	compute_final_color(int row, int col)
{
	t_vector3	total_color;
	uint32_t	img_color;
	uint32_t	final_color;
	int			width;
	int			index;

	index = -1;
	total_color = (t_vector3){0.0, 0.0, 0.0};
	while (++index < get_program()->image_count)
	{
		width = get_program()->canvas_width;
		img_color = get_program()->image_buffer[index][row * width + col];
		total_color.x += img_color >> 16;
		total_color.y += (img_color >> 8) & 0xFF;
		total_color.z += img_color & 0xFF;
	}
	final_color = color_clamp(
		((u_int32_t) (total_color.x / get_program()->image_count) << 16)
		| ((u_int32_t) (total_color.y / get_program()->image_count) << 8)
		| (u_int32_t) (total_color.z / get_program()->image_count)
	);
	mlx_put_pixel(get_program()->image, col, row, (final_color << 8 | 255));
}
