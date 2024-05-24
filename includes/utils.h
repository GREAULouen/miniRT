/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:47:35 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/24 12:53:52 by lgreau           ###   ########.fr       */
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

t_vector3		*sol_to_point(double intersect, t_vector3 *ray);

double			ft_v3_length(t_vector3 *v);

/*	~~~~~~~~~~~~~~~~ COLOR ~~~~~~~~~~~~~~~~	*/

uint32_t		get_red(uint32_t color);
uint32_t		get_green(uint32_t color);
uint32_t		get_blue(uint32_t color);

uint32_t		color_k_mult(uint32_t color, int k);
uint32_t		color_scal_mult(uint32_t color, double k);
uint32_t		color_add(uint32_t color1, uint32_t color2);
uint32_t		color_add_scal(uint32_t color1, double k, uint32_t color2);

#endif
