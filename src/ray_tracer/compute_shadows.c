/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_shadows.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:08:01 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/05 14:59:13 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_in_shadow(t_vector3 *new_og, t_vector3 *light_pos)
{
	t_program	*program;
	t_vector3	*ray;
	int			index;
	double		min_value;
	double		intersect;

	program = get_program();
	ray = ft_v3_dir(new_og, light_pos);
	index = -1;
	min_value = INFINITY;
	while (++index < program->object_count)
	{
		if ((int) program->objects[index].type > CAMERA)
		{
			intersect = get_obj_intersect()[program->objects[index].type]
				(new_og, ray, &program->objects[index], valid_sol_till_spot);
			if (intersect != INFINITY && intersect < min_value)
				min_value = intersect;
		}
	}
	free(ray);
	return (min_value != INFINITY);
}
