/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_final_color.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 15:25:37 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/04 11:42:12 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	compute_final_color(int row, int col)
{
	t_vector3	total_color;
	uint32_t	final_color;

	total_color = get_program()->avg_buffer[row * get_program()->canvas_width + col];
	ft_v3_indiv(&total_color, get_program()->image_count);
	final_color = color_clamp(
		((u_int32_t) (total_color.x) << 16)
		| ((u_int32_t) (total_color.y) << 8)
		| (u_int32_t) (total_color.z)
	);
	mlx_put_pixel(get_program()->image, col, row, (final_color << 8) | 255);
}
