/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:47:35 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/23 17:50:45 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void			free_arr(char **arr, int last, int is_allocated);
void			print_object(t_scene_object *obj);
void			print_objects(void);

int				get_object_type(char *type);
uint32_t		atoc(char *arg);
t_vector3		*atov(char *arg);

t_scene_object	*get_object(int type);

#endif
