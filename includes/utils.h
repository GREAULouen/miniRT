/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:47:35 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/31 11:11:53 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void			free_arr(char **arr, int last, int is_allocated);
int				get_length(char **arr);
void			print_object(t_scene_object *obj);
void			print_objects(void);

int				get_object_type(char *type);
uint32_t		atoc(char *arg);
t_vector3		*atov(char *arg);

t_scene_object	*get_object(int type);

/*	~~~~~~~~~~~~~~~ INTERSECT ~~~~~~~~~~~~~~~~	*/

t_vector3		*sol_to_point(double intersect, t_vector3 *ray, t_vector3 *og, t_scene_object *obj);
double			closest_intersection(double t1, double t2, t_vector3 *ray, t_vector3 *og);
int				valid_sol_from_cam(double sol);
int				valid_sol_till_spot(double sol);
int				solve_quadratic(double a, double b, double c, double sol[2]);

/*	~~~~~~~~~~~~~~~~ VECTOR3 ~~~~~~~~~~~~~~~~	*/

double			ft_v3_length(t_vector3 *v);
t_vector3		*ft_v3_cross_product(t_vector3 *v1, t_vector3 *v2);
void			ft_v3_innormalize(t_vector3 *v);

/*	~~~~~~~~~~~~~~~~ MATRIX ~~~~~~~~~~~~~~~~	*/

void			ft_rotation_matrix(t_vector3 *dir, t_matrix *rot);
void			ft_apply_rotate(t_vector3 *dir, t_matrix *rot, t_vector3 *res);
void			ft_invert_rot_matrix(t_matrix *og, t_matrix *inv);

/*	~~~~~~~~~~~~~~~~ COLOR ~~~~~~~~~~~~~~~~	*/

uint32_t		get_red(uint32_t color);
uint32_t		get_green(uint32_t color);
uint32_t		get_blue(uint32_t color);

uint32_t		color_sub(uint32_t color1, uint32_t color2);
uint32_t		color_scal_mult(uint32_t color, double k);
uint32_t		color_add(uint32_t color1, uint32_t color2);
uint32_t		color_add_scal(uint32_t color1, double k, uint32_t color2);
uint32_t		color_rem_opposite(uint32_t color1, uint32_t color2);

#endif
