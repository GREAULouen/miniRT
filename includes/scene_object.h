/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_object.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:50:25 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/05 16:29:15 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_OBJECT_H
# define SCENE_OBJECT_H

typedef double				t_matrix[3][3];

typedef enum e_scene_object_type
{
	AMBIENT_LIGHT,
	SPOT_LIGHT,
	CAMERA,
	PLANE,
	SPHERE,
	CYLINDER,
	CONE,
	OBJECT_TYPE_COUNT
}							t_scene_object_type;

# define SHIFT_R 16
# define SHIFT_G 8

# define COLOR_R 0xFF0000
# define COLOR_G 0x00FF00
# define COLOR_B 0x0000FF

# define EPSILON 0.0000001

typedef struct s_scene_object
{
	uint32_t				color;
	double					shininess;
	double					reflectiveness;
	t_scene_object_type		type;
	union {
		struct
		{
			double			intensity;
		}	s_ambient_light;
		struct
		{
			t_vector3		*pos;
			double			intensity;
		}	s_spot_light;
		struct
		{
			t_vector3		*pos;
			t_vector3		*dir;
			int				fov;
			double			view_plane;
			t_matrix		rot;
		}	s_camera;
		struct
		{
			t_vector3		*pos;
			t_vector3		*normal;
			double			dot;
			int				is_finite;
			double			width;
			double			height;
		}	s_plane;
		struct
		{
			t_vector3		*pos;
			double			diameter;
			double			sq_rad;
		}	s_sphere;
		struct
		{
			t_vector3		*pos;
			t_vector3		*dir;
			double			diameter;
			double			sq_rad;
			double			height;
		}	s_cylinder;
		struct
		{
			t_vector3		*pos;
			t_vector3		*dir;
			double			diameter;
			double			height;
			double			tan_theta;
			double			sq_tan_theta;
			t_matrix		rot;
			t_matrix		inv_rot;
		}	s_cone;
	};
}							t_scene_object;

typedef struct s_is_cylinder
{
	t_scene_object	*obj;
	double			delta;
	double			t[4];
	t_vector3 		*og;
	t_vector3 		*ray;
	t_vector3		*cross_ray_dir;
	t_vector3		*cross_pos_dir;
	t_vector3		*obj_org_pos;
	double			dot_dir;
	double			dot_pos_cross_ray_dir;
	double			dot_crossraydir;
	double			dot_crossraydir_crossposdir;
}				t_is_cylinder;

/*	~~~~~~~~~~~~~~~~ CREATION ~~~~~~~~~~~~~~~~	*/

typedef int					(*t_obj_creator)(t_scene_object *, int, char **);

int							create_ambient_light(t_scene_object *obj, int argc,
								char **args);
int							create_spot_light(t_scene_object *obj, int argc,
								char **args);
int							create_camera(t_scene_object *obj, int argc,
								char **args);
void						update_viewport(t_scene_object *obj);
int							create_plane(t_scene_object *obj, int argc,
								char **args);
int							create_sphere(t_scene_object *obj, int argc,
								char **args);
int							create_cylinder(t_scene_object *obj, int argc,
								char **args);
int							create_cone(t_scene_object *obj, int argc,
								char **args);

/*	~~~~~~~~~~~~~~~~ CLEANUP ~~~~~~~~~~~~~~~~	*/

typedef void				(*t_obj_cleanup)(t_scene_object *);

void						cleanup_spot_light(t_scene_object *obj);
void						cleanup_camera(t_scene_object *obj);
void						cleanup_plane(t_scene_object *obj);
void						cleanup_sphere(t_scene_object *obj);
void						cleanup_cylinder(t_scene_object *obj);
void						cleanup_cone(t_scene_object *obj);

/*	~~~~~~~~~~~~ INTERSECTION_CALC ~~~~~~~~~~~~	*/

typedef double				(*t_obj_intersect)(t_vector3 *, t_vector3 *,
								t_scene_object *, int (*)(double));

double						intersect_sphere(t_vector3 *og, t_vector3 *ray,
								t_scene_object *obj, int (*is_valid)(double));
double						intersect_plane(t_vector3 *og, t_vector3 *ray,
								t_scene_object *obj, int (*is_valid)(double));
double						intersect_cone(t_vector3 *og, t_vector3 *ray,
								t_scene_object *obj, int (*is_valid)(double));
double						intersect_cylinder(t_vector3 *og, t_vector3 *ray, t_scene_object *obj, int (*is_valid)(double));
double 						intersect_cylinder_endcaps(t_vector3 *og, t_vector3	*obj_org_pos, t_vector3 *ray, t_scene_object *obj);
double						intersect_cylinder_side(t_is_cylinder *is_cylinder, int (*is_valid)(double));
double						signed_distance_t_cylinder(t_vector3 *og, t_vector3 *ray, t_scene_object *obj, double distance);
double						signed_distance_t_cylinder_point(t_vector3 *point, t_vector3 *og, t_scene_object *obj);
t_vector3					*normal_sides(double signed_distance, t_vector3 *point, t_scene_object *obj);

/*	~~~~~~~~~~~~~~~ NORMAL_CALC ~~~~~~~~~~~~~~~	*/

typedef t_vector3*			(*t_obj_normal)(t_vector3 *, t_vector3 *,
								t_scene_object *);

t_vector3					*normal_sphere(t_vector3 *og, t_vector3 *point,
								t_scene_object *obj);
t_vector3					*normal_plane(t_vector3 *og, t_vector3 *point,
								t_scene_object *obj);
t_vector3					*normal_cone(t_vector3 *og, t_vector3 *point,
								t_scene_object *obj);
t_vector3					*normal_cylinder(t_vector3 *og, t_vector3 *point, t_scene_object *obj);

/*	~~~~~~~~~~~~~~~~~ GETTERS ~~~~~~~~~~~~~~~~~	*/

t_obj_creator				*get_obj_creator(void);
t_obj_cleanup				*get_obj_cleanup(void);
const t_obj_intersect		*get_obj_intersect(void);
const t_obj_normal			*get_obj_normal(void);

#endif
