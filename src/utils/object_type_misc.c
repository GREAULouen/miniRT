/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_type_misc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:12:39 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/28 14:44:32 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	print_object3(t_scene_object *obj)
{
	if (obj->type == CYLINDER)
	{
		print_v3("      |- position ", obj->s_cylinder.pos, ONELINE);
		print_v3("      |- normal   ", obj->s_cylinder.dir, ONELINE);
		printf("      |- diameter : %f\n", obj->s_cylinder.diameter);
		printf("      |- height   : %f\n", obj->s_cylinder.height);
		printf("      |- color    : (%u, %u, %u)\n",
			obj->color >> SHIFT_R,
			(obj->color & COLOR_G) >> SHIFT_G,
			obj->color & COLOR_B);
	}
}

static void	print_object2(t_scene_object *obj)
{
	if (obj->type == PLANE)
	{
		print_v3("      |- position ", obj->s_plane.pos, ONELINE);
		print_v3("      |- normal   ", obj->s_plane.normal, ONELINE);
		printf("      |- color    : (%u, %u, %u)\n",
			obj->color >> SHIFT_R,
			(obj->color & COLOR_G) >> SHIFT_G,
			obj->color & COLOR_B);
	}
	else if (obj->type == SPHERE)
	{
		print_v3("      |- position ", obj->s_sphere.pos, ONELINE);
		printf("      |- diameter : %f\n", obj->s_sphere.diameter);
		printf("      |- color    : (%u, %u, %u)\n",
			obj->color >> SHIFT_R,
			(obj->color & COLOR_G) >> SHIFT_G,
			obj->color & COLOR_B);
	}
	else
		print_object3(obj);
}

/**
 * @brief Prints relevant information about the object
 *
 * @param obj
 */
void	print_object(t_scene_object *obj)
{
	if (obj->type == AMBIENT_LIGHT)
	{
		printf("      |- intensity : %f\n", obj->s_ambient_light.intensity);
		printf("      |- color     : (%u, %u, %u)\n",
			obj->color >> SHIFT_R,
			(obj->color & COLOR_G) >> SHIFT_G,
			obj->color & COLOR_B);
	}
	else if (obj->type == CAMERA)
	{
		print_v3("      |- position  ", obj->s_camera.pos, ONELINE);
		print_v3("      |- direction ", obj->s_camera.dir, ONELINE);
		printf("      |- fov       : %u\n", obj->s_camera.fov);
	}
	else if (obj->type == SPOT_LIGHT)
	{
		print_v3("      |- position   ", obj->s_spot_light.pos, ONELINE);
		printf("      |- intensity : %f\n", obj->s_spot_light.intensity);
		printf("      |- color     : (%u, %u, %u)\n",
			obj->color >> SHIFT_R,
			(obj->color & COLOR_G) >> SHIFT_G,
			obj->color & COLOR_B);
	}
	else
		print_object2(obj);
}

static char	*get_type_string(int type)
{
	static	char	*type_string[OBJECT_TYPE_COUNT];

	type_string[AMBIENT_LIGHT] = "Ambient light";
	type_string[SPOT_LIGHT] = "Spot light";
	type_string[CAMERA] = "Camera";
	type_string[PLANE] = "Plane";
	type_string[SPHERE] = "Sphere";
	type_string[CYLINDER] = "Cylinder";
	return (type_string[type]);
}

void	print_objects(void)
{
	int	index;

	index = -1;
	printf("  |- objects:\n");
	while (++index < get_program()->object_count)
	{
		printf("    |- %s:\n",
			get_type_string(get_program()->objects[index].type));
		if (get_program()->objects[index].type > CAMERA)
			printf("  |- shininess: %f\n", get_program()->objects[index].shininess);
		print_object(&get_program()->objects[index]);
	}
}
