/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_object_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:50:24 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/05 16:30:33 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_obj_creator	*get_obj_creator(void)
{
	static t_obj_creator	obj_creator[OBJECT_TYPE_COUNT];

	obj_creator[AMBIENT_LIGHT] = create_ambient_light;
	obj_creator[SPOT_LIGHT] = create_spot_light;
	obj_creator[CAMERA] = create_camera;
	obj_creator[PLANE] = create_plane;
	obj_creator[SPHERE] = create_sphere;
	obj_creator[CYLINDER] = create_cylinder;
	obj_creator[CONE] = create_cone;
	return (&obj_creator[0]);
}

t_obj_cleanup	*get_obj_cleanup(void)
{
	static t_obj_cleanup	obj_cleanup[OBJECT_TYPE_COUNT];

	obj_cleanup[AMBIENT_LIGHT] = NULL;
	obj_cleanup[SPOT_LIGHT] = cleanup_spot_light;
	obj_cleanup[CAMERA] = cleanup_camera;
	obj_cleanup[PLANE] = cleanup_plane;
	obj_cleanup[SPHERE] = cleanup_sphere;
	obj_cleanup[CYLINDER] = cleanup_cylinder;
	obj_cleanup[CONE] = cleanup_cone;
	return (&obj_cleanup[0]);
}

const t_obj_intersect	*get_obj_intersect(void)
{
	static const t_obj_intersect	obj_intersect[OBJECT_TYPE_COUNT] = {
		NULL,
		NULL,
		NULL,
		intersect_plane,
		intersect_sphere,
		intersect_cylinder,
		intersect_cone
	};

	return (&obj_intersect[0]);
}

const t_obj_normal	*get_obj_normal(void)
{
	static const t_obj_normal	obj_normal[OBJECT_TYPE_COUNT] = {
		NULL,
		NULL,
		NULL,
		normal_plane,
		normal_sphere,
		normal_cylinder,
		normal_cone
	};

	return (&obj_normal[0]);
}
