/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:20:05 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/21 14:22:40 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define UNIQUE_OBJ_COUNT_A 0b00000001
# define UNIQUE_OBJ_COUNT_C 0b00000010

void			parse_input(void);

int				create_ambient_light(t_scene_object *obj, char **args);
int				create_camera(t_scene_object *obj, char **args);
int				create_spot_light(t_scene_object *obj, char **args);
int				create_plane(t_scene_object *obj, char **args);
int				create_sphere(t_scene_object *obj, char **args);
int				create_cylinder(t_scene_object *obj, char **args);

#endif