/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:10:17 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/28 10:58:30 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Loops through the pixel on the screen, creating the corresponding ray
 * & giving it to a calculation function
 *
 */
void	init_ray(void)
{
	t_program	*program;
	t_vector3	ray;
	t_vector3	tmp;
	int			row;
	int			col;
	uint32_t	pixel_color;

	row = -1;
	program = get_program();
	ray.z = get_object(CAMERA)->s_camera.view_plane;
	while (++row < program->canvas_height)
	{
		ray.y = program->half_view_height - (((double)row) * program->vc_height_ratio);
		col = -1;
		while (++col < program->canvas_width)
		{
			ray.x = program->half_view_width - (((double) col) * program->vc_width_ratio);
			ft_apply_rotate(&ray, &get_object(CAMERA)->s_camera.rot, &tmp);
			pixel_color = compute_intersection(&tmp);
			mlx_put_pixel(program->image, col, row, (pixel_color << 8 | 255));
		}
	}
}
