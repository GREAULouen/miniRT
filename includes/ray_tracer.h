/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:19:51 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/25 11:32:09 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TRACER_H
# define RAY_TRACER_H

void		init_ray(void);
void		rotate_ray(t_vector3 *ray, t_vector3 *res);

uint32_t	compute_intersection(t_vector3 *ray);
uint32_t	compute_light(double intersect, t_vector3 *ray, t_scene_object *obj);
int			is_in_shadow(t_vector3 *new_og, t_vector3 *light_pos);

#endif
