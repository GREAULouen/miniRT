/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_object.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:50:25 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/22 16:03:13 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_OBJECT_H
# define SCENE_OBJECT_H

# include "lib/libft/libft.h"

typedef enum e_scene_object_type
{
	AMBIENT_LIGHT,
	SPOT_LIGHT,
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

# define DEFAULT_WIDTH 1920
# define DEFAULT_HEIGHT 1080

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
		}	s_spot_light;
		struct
		{
			t_vector3		*pos;
			t_vector3		*dir;
			int				fov;
			double			view_plane;
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

/*	~~~~~~~~~~~~~~~~ CREATION ~~~~~~~~~~~~~~~~	*/
int							create_ambient_light(t_scene_object *obj,
								char **args);
int							create_spot_light(t_scene_object *obj, char **args);
int							create_camera(t_scene_object *obj, char **args);
int							create_plane(t_scene_object *obj, char **args);
int							create_sphere(t_scene_object *obj, char **args);
int							create_cylinder(t_scene_object *obj, char **args);

#endif
