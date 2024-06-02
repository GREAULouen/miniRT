/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_object_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:50:24 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/31 11:16:44 by lgreau           ###   ########.fr       */
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

t_obj_intersect	*get_obj_intersect(void)
{
	static t_obj_intersect	obj_intersect[OBJECT_TYPE_COUNT];

	obj_intersect[AMBIENT_LIGHT] = NULL;
	obj_intersect[SPOT_LIGHT] = NULL;
	obj_intersect[CAMERA] = NULL;
	obj_intersect[PLANE] = intersect_plane;
	obj_intersect[SPHERE] = intersect_sphere;
	obj_intersect[CYLINDER] = NULL;
	obj_intersect[CONE] = intersect_cone;
	return (&obj_intersect[0]);
}

t_obj_normal	*get_obj_normal(void)
{
	static t_obj_normal	obj_normal[OBJECT_TYPE_COUNT];

	obj_normal[AMBIENT_LIGHT] = NULL;
	obj_normal[SPOT_LIGHT] = NULL;
	obj_normal[CAMERA] = NULL;
	obj_normal[PLANE] = normal_plane;
	obj_normal[SPHERE] = normal_sphere;
	obj_normal[CYLINDER] = NULL;
	obj_normal[CONE] = normal_cone;
	return (&obj_normal[0]);
}
