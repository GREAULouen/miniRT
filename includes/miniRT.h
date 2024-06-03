/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:48:52 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/03 12:48:14 by lgreau           ###   ########.fr       */
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
# include "utils.h"
# include "parser.h"
# include "ray_tracer.h"
# include "mlx.h"
# include "error.h"

/* ~~~~ Other libraries ~~~	*/
# include <math.h>		// math
# include <unistd.h>	// read, write, close
# include <fcntl.h>		// open & flags
# include <stdio.h>		// printf, perror
# include <stdlib.h>	// malloc, free				| bonus: rand for anti_aliasing
# include <string.h>	// strerror

/* ~~~~ Main structure ~~~~	*/

# define IMG_BUFFER_COUNT 50

typedef struct s_program
{
	char			*file_name;
	int				canvas_width;
	int				canvas_height;
	double			viewport_width;
	double			half_view_width;
	double			viewport_height;
	double			half_view_height;
	double			vc_width_ratio;
	double			vc_height_ratio;
	int				object_count;
	t_scene_object	*objects;
	int				max_reflections;
	mlx_t			*mlx;
	int				image_count;
	mlx_image_t		*image;
	t_vector3		*avg_buffer;
}					t_program;

t_program			*get_program(void);
void				cleanup_program(void);
void				part_cleanup_program(int last);

/* ~ Argument validation ~	*/
# define BAD_ARGS_FORMAT "Bad program arguments.\n"

#endif
