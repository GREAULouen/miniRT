/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:01:50 by pgrossma          #+#    #+#             */
/*   Updated: 2024/05/28 13:52:51 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	loop_mlx(void *param)
{
	(void) param;
	init_ray();
	ft_v3_inadd(get_object(SPHERE)->s_sphere.pos, &(t_vector3){1.0, 1.0, 1.0});
	// get_object(CAMERA)->s_camera.pos->y += 1.0;
	// ft_inrotate_x(get_object(CAMERA)->s_camera.dir, 0.1);
	// ft_rotation_matrix(get_object(CAMERA)->s_camera.dir, &get_object(CAMERA)->s_camera.rot);
}

void	start_mlx(void)
{
	t_program	*program;

	program = get_program();
	program->mlx = mlx_init(program->canvas_width, program->canvas_height, PROGRAM_NAME, true);
	if (program->mlx == NULL)
	{
		ft_putstr_fd((char *) mlx_strerror(mlx_errno), 2);
		return ;
	}
	program->image = mlx_new_image(program->mlx, program->canvas_width, program->canvas_height);
	if (program->image == NULL)
	{
		ft_putstr_fd((char *) mlx_strerror(mlx_errno), 2);
		return ;
	}
	if (mlx_image_to_window(program->mlx, program->image, 0, 0) == -1)
	{
		ft_putstr_fd((char *) mlx_strerror(mlx_errno), 2);
		return ;
	}
	mlx_loop_hook(program->mlx, loop_mlx, NULL);
	mlx_loop(program->mlx);
	mlx_terminate(program->mlx);
}
