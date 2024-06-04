/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:58:46 by pgrossma          #+#    #+#             */
/*   Updated: 2024/06/04 15:22:55 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	loop_hook(void *param)
{
	t_program	*program;
	int			index;

	program = get_program();
	(void) param;
	if (program->max_image_buffering > 0 && program->image_count + 1 < program->max_image_buffering)
		++program->image_count;
	if (program->thread_count <= 0)
		init_ray((void *)0);
	else
	{
		index = -1;
		while (++index < program->thread_count)
			pthread_create(&program->rendering_thread[index], NULL, init_ray, (void *)&index);
		index = -1;
		while (++index < program->thread_count)
			pthread_join(program->rendering_thread[index], NULL);
	}
}
