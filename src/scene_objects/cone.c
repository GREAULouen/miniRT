/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:28:57 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/30 17:37:22 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	create_cone(t_scene_object *obj, int argc, char **args)
{
	if (argc < 6)
		return (rt_perror((char *)__func__, WRONG_ARGUMENT_COUNT), -1);
	obj->type = CONE;
	obj->s_cone.diameter = ft_atod(args[3]);
	if (obj->s_cone.diameter < 0.0)
		return (rt_perror((char *)__func__, DIAMETER_OUT_OF_RANGE), -1);
	obj->s_cone.height = ft_atod(args[4]);
	if (obj->s_cone.height < 0.0)
		return (rt_perror((char *)__func__, HEIGHT_OUT_OF_RANGE), -1);
	obj->s_cone.tan_theta = obj->s_cone.diameter / (2.0 * obj->s_cone.height);
	obj->color = atoc(args[5]);
	obj->s_cone.pos = atov(args[1]);
	if (!obj->s_cone.pos)
		return (-1);
	obj->s_cone.dir = atov(args[2]);
	if (!obj->s_cone.dir)
		return (free(obj->s_cone.pos), -1);
	ft_v3_innormalize(obj->s_cone.dir);
	ft_rotation_matrix(obj->s_cone.dir, &obj->s_cone.rot);
	ft_invert_rot_matrix(&obj->s_cone.rot, &obj->s_cone.inv_rot);
	return (0);
}

void	cleanup_cone(t_scene_object *obj)
{
	if (!obj)
		return ;
	free(obj->s_cone.pos);
	free(obj->s_cone.dir);
}
