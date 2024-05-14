/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_object.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:50:25 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/14 14:06:31 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_OBJECT_H
# define SCENE_OBJECT_H

# include "lib/libft/libft.h"

typedef enum e_scene_object_type
{
	AMBIENT_LIGHT,
	DIRECTIONAL_LIGHT,
	CAMERA,
	PLANE,
	SPHERE,
	CYLINDER
}							t_scene_object_type;

typedef struct s_scene_object
{
	t_scene_object_type		type;
	uint32_t				color;
	union {
		struct
		{
			float			intensity;
		}	s_ambient_light;
		struct
		{
			float			intensity;
			t_vector3		dir;
		}	s_directional_light;
		struct
		{
			t_vector3		pos;
			t_vector3		dir;
			unsigned int	fov;
		}	s_camera;
		struct
		{
			t_vector3		pos;
			t_vector3		normal;
		}	s_plane;
		struct
		{
			t_vector3		pos;
			float			diameter;
		}	s_sphere;
		struct
		{
			t_vector3		pos;
			t_vector3		dir;
			float			diameter;
			float			height;
		}	s_cylinder;
	};
}							t_scene_object;

#endif
