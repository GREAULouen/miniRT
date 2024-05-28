/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:01:50 by pgrossma          #+#    #+#             */
/*   Updated: 2024/05/28 12:12:28 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	loop_hook(void *param)
{
	(void) param;
	init_ray();
	// get_object(CAMERA)->s_camera.pos->y += 1.0;
}

void	register_hooks(mlx_t *mlx)
{
	mlx_loop_hook(mlx, loop_hook, NULL);
	mlx_resize_hook(mlx, resize_hook, NULL);
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
	register_hooks(program->mlx);
	mlx_loop(program->mlx);
	mlx_terminate(program->mlx);
}
