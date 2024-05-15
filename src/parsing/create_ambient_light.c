/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ambient_light.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:58:00 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/15 10:57:42 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Initialize an ambient light using the args as values
 *
 * @param type
 * @param args
 * @return int : -1 if error else 0
 */
int	create_ambient_light(t_scene_object *obj, char **args)
{
	if (!args[1] || !args[2] || args[3])
		return (set_error((char *)__func__, INVALID_ARG), -1);
	obj->type = AMBIENT_LIGHT;
	obj->s_ambient_light.intensity = ft_atod(args[1]);
	if (obj->s_ambient_light.intensity < 0
		|| obj->s_ambient_light.intensity > 1)
		return (set_error((char *)__func__, INVALID_ARG), -1);
	obj->s_ambient_light.color = atoc(args[2]);
	return ((*get_errno() == NO_ERROR) - 1);
}
