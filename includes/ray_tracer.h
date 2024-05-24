/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:19:51 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/24 14:06:43 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TRACER_H
# define RAY_TRACER_H

void		init_ray(void);
uint32_t	compute_intersection(t_vector3 *ray);
uint32_t	compute_light(double intersect, t_vector3 *ray, t_scene_object *obj);

#endif
