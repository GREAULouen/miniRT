/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:58:46 by pgrossma          #+#    #+#             */
/*   Updated: 2024/06/04 12:31:41 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	loop_hook(void *param)
{
	t_program	*program;
	int			*tmp;
	int			index;

	program = get_program();
	(void) param;
	if (program->image_count + 1 < program->max_image_buffering)
		++program->image_count;
	tmp = (int[2]){0, program->canvas_height};
	if (program->thread_count <= 0)
		init_ray((void *)tmp);
	else
	{
		index = -1;
		while (++index < program->thread_count)
		{
			tmp = (int[2]){
				index * program->row_per_thread,
				(index + 1) * program->row_per_thread
			};
			if (index + 1 == program->thread_count)
				tmp[1] = program->canvas_height;
			pthread_create(&program->rendering_thread[index], NULL, init_ray, (void *)tmp);
		}
		index = -1;
		while (++index < program->thread_count)
			pthread_join(program->rendering_thread[index], NULL);
	}
}
