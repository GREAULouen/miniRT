/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_specular_reflection.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:53:19 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/28 14:54:30 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

uint32_t	compute_spec_reflection(t_vector3 *point, t_scene_object *light, t_scene_object *obj)
