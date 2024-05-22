/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:48:52 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/22 14:04:03 by lgreau           ###   ########.fr       */
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
	int				screen_width;
	int				screen_height;
	int				object_count;
	t_scene_object	*objects;
}					t_program;

t_program			*get_program(void);

/* ~ Argument validation ~	*/
# define BAD_ARGS_FORMAT "Bad program arguments.\n"

#endif
