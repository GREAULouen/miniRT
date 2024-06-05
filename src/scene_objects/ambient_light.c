/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:58:00 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/05 18:36:06 by lgreau           ###   ########.fr       */
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
int	create_ambient_light(t_scene_object *obj, int argc, char **args)
{
	if (argc < 3 || !args[1] || !args[2])
		return (rt_perror((char *)__func__, WRONG_ARGUMENT_COUNT), -1);
	obj->type = AMBIENT_LIGHT;
	obj->color = atoc(args[2]);
	if (obj->color == (uint32_t)-1)
		return (-1);
	obj->s_ambient_light.intensity = ft_atod(args[1]);
	if (obj->s_ambient_light.intensity < 0
		|| obj->s_ambient_light.intensity > 1)
		return (rt_perror((char *)__func__, INTENSITY_OUT_OF_RANGE), -1);
	return ((*get_errno() == NO_ERROR) - 1);
}
