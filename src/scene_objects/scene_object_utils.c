/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_object_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:50:24 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/24 11:03:56 by lgreau           ###   ########.fr       */
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
	return (&obj_cleanup[0]);
}

t_obj_intersect	*get_obj_intersect(void)
{
	static t_obj_intersect	obj_intersect[OBJECT_TYPE_COUNT];

	obj_intersect[AMBIENT_LIGHT] = NULL;
	obj_intersect[SPOT_LIGHT] = NULL;
	obj_intersect[CAMERA] = NULL;
	obj_intersect[PLANE] = NULL;
	obj_intersect[SPHERE] = intersect_sphere;
	obj_intersect[CYLINDER] = NULL;
	return (&obj_intersect[0]);
}

t_obj_normal	*get_obj_normal(void)
{
	static t_obj_normal	obj_normal[OBJECT_TYPE_COUNT];

	obj_normal[AMBIENT_LIGHT] = NULL;
	obj_normal[SPOT_LIGHT] = NULL;
	obj_normal[CAMERA] = NULL;
	obj_normal[PLANE] = NULL;
	obj_normal[SPHERE] = normal_sphere;
	obj_normal[CYLINDER] = NULL;
	return (&obj_normal[0]);
}
