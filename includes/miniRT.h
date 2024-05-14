/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:48:52 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/14 14:28:55 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/* git submodules libraries	*/
# include "lib/libft/libft.h"
# include "lib/MLX42/include/MLX42/MLX42.h"

/* ~~~~ local includes ~~~~	*/
# include "scene_object.h"

/* ~~~~ Other libraries ~~~	*/
# include <math.h>		// math
# include <unistd.h>	// open, read, write, close
# include <stdio.h>		// printf, perror
# include <stdlib.h>	// malloc, free
# include <string.h>	// strerror


/* ~~~~ Main structure ~~~~	*/
typedef struct s_program
{
	int				object_count;
	t_scene_object	*objects;
}					t_program;

t_program			*get_program(void);

#endif
