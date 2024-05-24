/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_shadows.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:08:01 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/24 16:36:28 by lgreau           ###   ########.fr       */
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
	// ft_v3_inadd(ray, new_og);
	index = -1;
	min_value = INFINITY;
	while (++index < program->object_count)	// Can be changed to only test intersection with Solid objects that have been pre-processed
	{
		if ((int) program->objects[index].type == SPHERE)	// Can be changed to only test intersection with Solid objects that have been pre-processed
		{
			intersect = get_obj_intersect()[program->objects[index].type](new_og, ray, &program->objects[index]);
			// print_v3("ray", ray, ONELINE);
			// printf("intersect solution: %f\n", intersect);
			if (intersect > EPSILON && intersect < (1 - EPSILON) && intersect < min_value)
				min_value = intersect;
		}
	}
	free(ray);
	return (min_value != INFINITY);
}
