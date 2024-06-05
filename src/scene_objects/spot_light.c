/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spot_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:43:27 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/05 18:44:41 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Initialize a spot light using the args as values
 *
 * @param type
 * @param args
 * @return int : -1 if error else 0
 */
int	create_spot_light(t_scene_object *obj, int argc, char **args)
{
	if (argc < 4 || !args[1] || !args[2] || !args[3])
		return (rt_perror((char *)__func__, WRONG_ARGUMENT_COUNT), -1);
	obj->type = SPOT_LIGHT;
	obj->color = atoc(args[3]);
	if (obj->color == (uint32_t)-1)
		return (-1);
	obj->s_spot_light.pos = atov(args[1]);
	if (!obj->s_spot_light.pos)
		return (-1);
	obj->s_spot_light.intensity = ft_atod(args[2]);
	if (obj->s_spot_light.intensity < 0
		|| obj->s_spot_light.intensity > 1)
		return (free(obj->s_spot_light.pos),
			rt_perror((char *)__func__, INTENSITY_OUT_OF_RANGE), -1);
	return (0);
}

void	cleanup_spot_light(t_scene_object *obj)
{
	if (!obj)
		return ;
	free(obj->s_spot_light.pos);
}
