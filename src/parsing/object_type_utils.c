/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_type_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:36:31 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/14 17:11:41 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_obj_creator	*get_obj_creator(void)
{
	static t_obj_creator	obj_creator[OBJECT_TYPE_COUNT];

	obj_creator[AMBIENT_LIGHT] = create_ambient_light;
	return (&obj_creator[0]);
}

int	get_object_type(char *type)
{
	if (!type)
		return (set_error((char *)__func__, INVALID_ARG), -1);
	if (ft_endswith(type, "A"))
		return (AMBIENT_LIGHT);
	if (ft_endswith(type, "L"))
		return (DIRECTIONAL_LIGHT);
	if (ft_endswith(type, "C"))
		return (CAMERA);
	if (ft_endswith(type, "pl"))
		return (PLANE);
	if (ft_endswith(type, "sp"))
		return (SPHERE);
	if (ft_endswith(type, "cy"))
		return (CYLINDER);
	return (-1);
}

/**
 * @brief Converts R,G,B to uint32 storing 00RRGGBB
 *
 * @param arg
 * @return uint32_t
 */
uint32_t	atoc(char *arg)
{
	uint32_t	color;
	int			tmp;
	char		**splt;

	color = 0;
	splt = ft_split(arg, ',');
	if (!splt)
		return (set_error((char *)__func__, ALLOC), -1);
	if (!splt[0] || !splt[1] || !splt[2] || splt[3])
		return (set_error((char *)__func__, INVALID_ARG), -1);
	tmp = ft_btoi(splt[0], BASE10_STR);
	if (*get_errno() != NO_ERROR || tmp < 0 || tmp >= 256)
		return (set_error((char *)__func__, INVALID_ARG), 0);
	color |= (tmp << SHIFT_R);
	tmp = ft_btoi(splt[1], BASE10_STR);
	if (*get_errno() != NO_ERROR || tmp < 0 || tmp >= 256)
		return (set_error((char *)__func__, INVALID_ARG), 0);
	color |= (tmp << SHIFT_G);
	tmp = ft_btoi(splt[2], BASE10_STR);
	if (*get_errno() != NO_ERROR || tmp < 0 || tmp >= 256)
		return (set_error((char *)__func__, INVALID_ARG), 0);
	color |= tmp;
	return (color);
}
