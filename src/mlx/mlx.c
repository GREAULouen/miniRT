/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:01:50 by pgrossma          #+#    #+#             */
/*   Updated: 2024/06/05 14:05:59 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	register_hooks(mlx_t *mlx)
{
	mlx_loop_hook(mlx, loop_hook, NULL);
	mlx_resize_hook(mlx, resize_hook, NULL);
	mlx_key_hook(mlx, key_hook, NULL);
}

bool	start_mlx(void)
{
	t_program	*program;

	program = get_program();
	program->mlx = mlx_init(program->canvas_width,
			program->canvas_height,
			PROGRAM_NAME, true);
	if (program->mlx == NULL)
		return (mlx_print_error());
	program->image = mlx_new_image(program->mlx,
			program->canvas_width,
			program->canvas_height);
	if (program->image == NULL)
		return (mlx_print_error());
	program->avg_buffer = ft_calloc(program->canvas_width
			* program->canvas_height, sizeof(t_vector3));
	if (!program->avg_buffer)
		return (false);
	if (mlx_image_to_window(program->mlx, program->image, 0, 0) == -1)
		return (mlx_print_error());
	register_hooks(program->mlx);
	mlx_loop(program->mlx);
	mlx_terminate(program->mlx);
	return (true);
}
