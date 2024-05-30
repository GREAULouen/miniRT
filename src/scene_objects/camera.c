/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:56:58 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/30 13:59:25 by lgreau           ###   ########.fr       */
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
int	create_camera(t_scene_object *obj, int argc, char **args)
{
	if (argc < 4 || !args[1] || !args[2] || !args[3])
		return (rt_perror((char *)__func__, WRONG_ARGUMENT_COUNT), -1);
	obj->type = CAMERA;
	obj->s_camera.pos = atov(args[1]);
	if (!obj->s_camera.pos)
		return (-1);
	obj->s_camera.dir = atov(args[2]);
	if (!obj->s_camera.dir)
		return (free(obj->s_camera.pos), -1);
	ft_v3_innormalize(obj->s_camera.dir);
	obj->s_camera.fov = ft_btoi(args[3], BASE10_STR);
	if (obj->s_camera.fov < 0 || obj->s_camera.fov > 180)
		return (free(obj->s_camera.pos),
			free(obj->s_camera.dir),
			rt_perror((char *)__func__, FOV_OUT_OF_RANGE), -1);
	update_viewport(obj);
	ft_rotation_matrix(obj->s_camera.dir, &obj->s_camera.rot);
	return (0);
}

void	update_viewport(t_scene_object *obj)
{
	obj->s_camera.view_plane = get_program()->viewport_width
		/ (2 * tan(M_PI * obj->s_camera.fov / 360));
}

void	cleanup_camera(t_scene_object *obj)
{
	if (!obj)
		return ;
	free(obj->s_camera.pos);
	free(obj->s_camera.dir);
}
