/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_type_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:36:31 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/31 11:19:31 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_object_type(char *type)
{
	if (!type)
		return (set_error((char *)__func__, INVALID_ARG), -1);
	if (ft_endswith(type, "A"))
		return (AMBIENT_LIGHT);
	if (ft_endswith(type, "L"))
		return (SPOT_LIGHT);
	if (ft_endswith(type, "C"))
		return (CAMERA);
	if (ft_endswith(type, "pl"))
		return (PLANE);
	if (ft_endswith(type, "sp"))
		return (SPHERE);
	if (ft_endswith(type, "cy"))
		return (CYLINDER);
	if (ft_endswith(type, "co"))
		return (CONE);
	return (-1);
}

/**
 * @brief Get the first occurence of scene object pointer from it's type
 *
 * @param type
 * @return t_scene_object*
 */
t_scene_object	*get_object(int type)
{
	int	index;

	index = -1;
	while (++index < get_program()->object_count)
		if ((int)get_program()->objects[index].type == type)
			return (&get_program()->objects[index]);
	return (NULL);
}
