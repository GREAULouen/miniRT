/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:01:50 by pgrossma          #+#    #+#             */
/*   Updated: 2024/05/28 14:17:18 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	loop_mlx(void *param)
{
	(void) param;
	init_ray();
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
