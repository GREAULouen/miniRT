/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_object.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:50:25 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/15 09:50:39 by lgreau           ###   ########.fr       */
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
	CYLINDER,
	OBJECT_TYPE_COUNT
}							t_scene_object_type;

# define SHIFT_R 16
# define SHIFT_G 8

# define COLOR_R 0xFF0000
# define COLOR_G 0x00FF00
# define COLOR_B 0x0000FF

typedef struct s_scene_object
{
	t_scene_object_type		type;
	union {
		struct
		{
			double			intensity;
			uint32_t		color;
		}	s_ambient_light;
		struct
		{
			t_vector3		*pos;
			double			intensity;
			uint32_t		color;
		}	s_directional_light;
		struct
		{
			t_vector3		*pos;
			t_vector3		*dir;
			int				fov;
		}	s_camera;
		struct
		{
			t_vector3		*pos;
			t_vector3		*normal;
			uint32_t		color;
		}	s_plane;
		struct
		{
			t_vector3		*pos;
			double			diameter;
			uint32_t		color;
		}	s_sphere;
		struct
		{
			t_vector3		*pos;
			t_vector3		*dir;
			double			diameter;
			double			height;
			uint32_t		color;
		}	s_cylinder;
	};
}							t_scene_object;

typedef int	(*t_obj_creator)(t_scene_object *, char **);

#endif
