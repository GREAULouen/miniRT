/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:10:17 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/22 15:09:07 by lgreau           ###   ########.fr       */
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
	double		view_plane;
	int			row;
	int			col;

	row = -1;
	program = get_program();
	view_plane = get_object(CAMERA)->s_camera.view_plane;
	while (++row < program->canvas_height)
	{
		col = -1;
		while (++col < program->canvas_width)
		{
			ray.x = col * program->viewport_width / program->canvas_width - program->viewport_width / 2;
			ray.y = (program->viewport_height / 2) - row * program->viewport_height / program->canvas_height;
			ray.z = view_plane;
		}
	}
}
