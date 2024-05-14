/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:00:11 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/14 18:37:10 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Initialize a camera using the args as values
 *
 * @param type
 * @param args
 * @return int : -1 if error else 0
 */
int	create_camera(t_scene_object *obj, char **args)
{
	obj->type = CAMERA;
	obj->s_camera.pos = atov(args[1]);
	if (!obj->s_camera.pos)
		return (-1);
	obj->s_camera.dir = atov(args[2]);
	if (!obj->s_camera.dir)
		return (free(obj->s_camera.pos), -1);
	if (ft_dot_product(obj->s_camera.dir, obj->s_camera.dir) >= 1)
		return (free(obj->s_camera.pos), free(obj->s_camera.dir),
				set_error((char *)__func__, INVALID_ARG), -1);
	obj->s_camera.fov = ft_btoi(args[3], BASE10_STR);
	if (obj->s_camera.fov < 0 || obj->s_camera.fov > 180)
		return (free(obj->s_camera.pos),
			free(obj->s_camera.dir),
			set_error((char *)__func__, INVALID_ARG), -1);
	return (0);
}
