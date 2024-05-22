/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:55:30 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/22 16:09:56 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Initialize a plane using the args as values
 *
 * @param type
 * @param args
 * @return int : -1 if error else 0
 */
int	create_plane(t_scene_object *obj, char **args)
{
	if (!args[1] || !args[2] || !args[3] || args[4])
		return (set_error((char *)__func__, INVALID_ARG), -1);
	obj->type = PLANE;
	obj->s_plane.pos = atov(args[1]);
	if (!obj->s_plane.pos)
		return (-1);
	obj->s_plane.normal = atov(args[2]);
	if (!obj->s_plane.normal)
		return (free(obj->s_plane.pos), -1);
	obj->s_plane.color = atoc(args[3]);
	return (0);
}

void	cleanup_plane(t_scene_object *obj)
{
	if (!obj)
		return ;
	free(obj->s_plane.pos);
	free(obj->s_plane.normal);
}
