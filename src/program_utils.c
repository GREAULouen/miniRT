/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:21:31 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/22 16:19:16 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_program	*get_program(void)
{
	static t_program	program;

	return (&program);
}

void	cleanup_program(void)
{
	t_program	*program;
	int			index;

	program = get_program();
	index = -1;
	while (++index < program->object_count)
		if ((int) program->objects[index].type != AMBIENT_LIGHT)
			get_obj_cleanup()[program->objects[index].type]
				(&program->objects[index]);
	free(program->objects);
}
