/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:19:51 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/03 14:57:39 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TRACER_H
# define RAY_TRACER_H

// # define BACKGROUND_COLOR 0x0
# define BACKGROUND_COLOR 0xB0B0B0

void		init_ray(void);
void		reflected_ray(t_vector3 *ray, t_vector3 *normal, t_vector3 *res);

uint32_t	compute_intersection(t_vector3 *og, t_vector3 *ray, int depth, int (*is_valid)(double));
uint32_t	compute_light(t_vector3 *point, t_vector3 *normal, t_vector3 *reflected, t_scene_object *obj);
int			is_in_shadow(t_vector3 *new_og, t_vector3 *light_pos);
void		compute_final_color(int row, int col);

#endif
