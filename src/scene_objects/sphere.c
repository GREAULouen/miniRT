/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:46:50 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/22 16:09:34 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Initialize a sphere using the args as values
 *
 * @param type
 * @param args
 * @return int : -1 if error else 0
 */
int	create_sphere(t_scene_object *obj, char **args)
{
	if (!args[1] || !args[2] || !args[3] || args[4])
		return (set_error((char *)__func__, INVALID_ARG), -1);
	obj->type = SPHERE;
	obj->s_sphere.pos = atov(args[1]);
	if (!obj->s_sphere.pos)
		return (-1);
	obj->s_sphere.diameter = ft_atod(args[2]);
	if (obj->s_sphere.diameter < 0)
		return (free(obj->s_sphere.pos),
			set_error((char *)__func__, INVALID_ARG), -1);
	obj->s_sphere.color = atoc(args[3]);
	return (0);
}

void	cleanup_sphere(t_scene_object *obj)
{
	if (!obj)
		return ;
	free(obj->s_sphere.pos);
}
