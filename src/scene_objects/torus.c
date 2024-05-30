/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:42:14 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/30 17:11:30 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	create_torus(t_scene_object *obj, int argc, char **args)
{
	if (argc < 6)
		return (rt_perror((char *)__func__, WRONG_ARGUMENT_COUNT), -1);
	obj->type = TORUS;
	obj->color = atoc(args[5]);
	obj->shininess = 0.0;
	if (argc > 6)
		obj->shininess = ft_atod(args[6]);
	obj->reflectiveness = 0.0;
	if (argc > 7)
		obj->reflectiveness = ft_atod(args[7]);
	obj->s_torus.minor_radius = ft_atod(args[3]);
	obj->s_torus.major_radius = ft_atod(args[4]);
	obj->s_torus.pos = atov(args[1]);
	if (!obj->s_torus.pos)
		return (-1);
	obj->s_torus.dir = atov(args[2]);
	if (!obj->s_torus.dir)
		return (free(obj->s_torus.pos), -1);
	ft_v3_innormalize(obj->s_torus.dir);
	ft_rotation_matrix(obj->s_torus.dir, &obj->s_torus.rot);
	ft_invert_rot_matrix(&obj->s_torus.rot, &obj->s_torus.inv_rot);
	return (0);
}

void	cleanup_torus(t_scene_object *obj)
{
	if (!obj)
		return ;
	free(obj->s_torus.pos);
	free(obj->s_torus.dir);
}

double	intersect_torus(t_vector3 *og, t_vector3 *ray, t_scene_object *obj, int (*is_valid)(double))
{
	t_vector3	n_og;
	t_vector3	n_dir;

	n_og = (t_vector3){og->x - obj->s_torus.pos->x, og->y - obj->s_torus.pos->y, og->z - obj->s_torus.pos->z};
	ft_apply_rotate(ray, &obj->s_torus.inv_rot, &n_dir);
}
