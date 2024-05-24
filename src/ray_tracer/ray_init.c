/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:10:17 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/24 12:17:47 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Loops through the pixel on the screen, creating the corresponding ray
 * & giving it to a calculation function
 *
 */
void	init_ray(void)
{
	t_program	*program;
	t_vector3	ray;
	int			row;
	int			col;
	uint32_t	pixel_color;

	row = -1;
	program = get_program();
	ray.z = get_object(CAMERA)->s_camera.view_plane;
	// printf("%f\n", program->viewport_height);
	while (++row < program->canvas_height)
	{
		ray.y = (program->viewport_height / 2.0) - (((double)row) * program->viewport_height / ((double) program->canvas_height));
		col = -1;
		while (++col < program->canvas_width)
		{
			ray.x = ((double) col) * program->viewport_width / ((double) program->canvas_width) - program->viewport_width / 2.0;
			// printf("ray @ [%d, %d]", row, col);
			// print_v3("", &ray, ONELINE);
			pixel_color = intersect_ray(&ray);
			mlx_put_pixel(program->image, col, row, (pixel_color << 8 | 255));
		}
	}
}

uint32_t	intersect_ray(t_vector3 *ray)
{
	t_program	*program;
	int			index;
	int			min;
	double		min_value;
	double		intersect;

	program = get_program();
	index = -1;
	min = index;
	min_value = INFINITY;
	while (++index < program->object_count)
	{
		if ((int) program->objects[index].type == SPHERE)
		{
			intersect = get_obj_intersect()[program->objects[index].type](ray, &program->objects[index]);
			if (intersect < min_value)
			{
				min = index;
				min_value = intersect;
			}
		}
	}
	if (min_value < INFINITY)
		return (color_scal_mult(program->objects[min].s_sphere.color, compute_light(min_value, ray, &program->objects[min])));
	return (color_scal_mult(get_object(AMBIENT_LIGHT)->s_ambient_light.color, get_object(AMBIENT_LIGHT)->s_ambient_light.intensity));
}

/**
 * @brief Computes the total intensity of light at the intersection with
 * the object
 *
 * @param intersect Point = Ray.og + intersect * Ray.dir
 * @param obj
 * @return double
 */
double	compute_light(double intersect, t_vector3 *ray, t_scene_object *obj)
{
	t_program	*program;
	t_vector3	*point_to_light;
	t_vector3	*point;
	t_vector3	*normal;
	double		dot;
	double		total_intensity;
	int			index;

	program = get_program();
	total_intensity = 0.0;
	index = -1;
	point = sol_to_point(intersect, ray);
	normal = get_obj_normal()[obj->type](point, obj);
	while (++index < program->object_count)
	{
		if ((int) program->objects[index].type == AMBIENT_LIGHT)
			total_intensity += program->objects[index].s_ambient_light.intensity;
		else if ((int) program->objects[index].type == SPOT_LIGHT)
		{
			point_to_light = ft_v3_dir(point, program->objects[index].s_spot_light.pos);
			dot = ft_dot_product(point_to_light, normal);
			if (dot > 0)
				total_intensity += program->objects[index].s_spot_light.intensity * dot / (ft_v3_length(normal) * ft_v3_length(point_to_light));
			free(point_to_light);
		}
	}
	free(point);
	free(normal);
	return (total_intensity);
}
