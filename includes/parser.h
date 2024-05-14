/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:20:05 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/14 16:36:18 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define UNIQUE_OBJ_COUNT_A 0b00000001
# define UNIQUE_OBJ_COUNT_C 0b00000010
# define UNIQUE_OBJ_COUNT_L 0b00000100

void			parse_input(void);

t_obj_creator	*get_obj_creator(void);
int				get_object_type(char *type);
uint32_t		atoc(char *arg);

int				create_ambient_light(t_scene_object *obj, char **args);

#endif
