/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_normal_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:18:39 by pgrossma          #+#    #+#             */
/*   Updated: 2024/06/04 19:23:25 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector3	*normal_sides(double signed_distance, t_vector3 *point,
		t_scene_object *obj)
{
	t_vector3	*normal;
	t_vector3	*sub_dir_pos;
	t_vector3	*mult_dir_dis;

	mult_dir_dis = ft_v3_mult(obj->s_cylinder.dir, signed_distance);
	if (mult_dir_dis == NULL)
		return (NULL);
	sub_dir_pos = ft_v3_sub(point, mult_dir_dis);
	if (sub_dir_pos == NULL)
		return (free(mult_dir_dis), NULL);
	normal = ft_v3_sub(sub_dir_pos, obj->s_cylinder.pos);
	free(sub_dir_pos);
	free(mult_dir_dis);
	if (normal == NULL)
		return (NULL);
	ft_v3_innormalize(normal);
	return (normal);
}
