/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:58:46 by pgrossma          #+#    #+#             */
/*   Updated: 2024/06/04 12:16:04 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	loop_hook(void *param)
{
	t_program	*program;
	int			*tmp;

	program = get_program();
	(void) param;
	if (program->image_count + 1 < program->max_image_buffering)
		++program->image_count;
	tmp = (int[2]){0, program->canvas_height};
	init_ray((void *)tmp);
}
