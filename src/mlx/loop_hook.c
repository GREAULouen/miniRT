/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:58:46 by pgrossma          #+#    #+#             */
/*   Updated: 2024/06/05 18:29:11 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	*get_thread_ids(void)
{
	static int	thread_id[MAX_THREAD_COUNT];
	int			index;

	index = -1;
	while (++index < MAX_THREAD_COUNT)
		thread_id[index] = index;
	return (&thread_id[0]);
}

void	loop_hook(void *param)
{
	t_program	*program;
	int			*thread_id;
	int			index;

	program = get_program();
	thread_id = get_thread_ids();
	(void) param;
	if (program->max_image_buffering > 0 && program->image_count + 1
		< program->max_image_buffering)
		++program->image_count;
	if (program->thread_count <= 0)
		init_ray((void *)0);
	else
	{
		index = -1;
		while (++index < program->thread_count)
			pthread_create(&program->rendering_thread[index], NULL,
				init_ray, (void *)&thread_id[index]);
		index = -1;
		while (++index < program->thread_count)
			pthread_join(program->rendering_thread[index], NULL);
	}
}
