/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:48:52 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/22 16:03:21 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define PROGRAM_NAME "miniRT"

/* git submodules libraries	*/
# include "lib/libft/libft.h"
# include "lib/MLX42/include/MLX42/MLX42.h"

/* ~~~~ local includes ~~~~	*/
# include "scene_object.h"
# include "parser.h"
# include "utils.h"
# include "ray_tracer.h"

/* ~~~~ Other libraries ~~~	*/
# include <math.h>		// math
# include <unistd.h>	// read, write, close
# include <fcntl.h>		// open & flags
# include <stdio.h>		// printf, perror
# include <stdlib.h>	// malloc, free
# include <string.h>	// strerror

/* ~~~~ Main structure ~~~~	*/
typedef struct s_program
{
	char			*file_name;
	int				canvas_width;
	int				canvas_height;
	double			viewport_width;
	double			viewport_height;
	int				object_count;
	t_scene_object	*objects;
}					t_program;

t_program			*get_program(void);

/* ~ Argument validation ~	*/
# define BAD_ARGS_FORMAT "Bad program arguments.\n"

#endif
