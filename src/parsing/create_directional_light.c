/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_directional_light.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:43:27 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/15 09:51:13 by lgreau           ###   ########.fr       */
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
int	create_directional_light(t_scene_object *obj, char **args)
{
	obj->type = DIRECTIONAL_LIGHT;
	obj->s_directional_light.pos = atov(args[1]);
	if (!obj->s_directional_light.pos)
		return (-1);
	obj->s_directional_light.intensity = ft_atod(args[2]);
	if (obj->s_directional_light.intensity < 0
		|| obj->s_directional_light.intensity > 1)
		return (free(obj->s_directional_light.pos),
				set_error((char *)__func__, INVALID_ARG), -1);
	obj->s_directional_light.color = atoc(args[3]);
	return (0);
}
