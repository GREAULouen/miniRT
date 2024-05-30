/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:32:45 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/30 13:47:07 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef enum e_error_types
{
	INTENSITY_OUT_OF_RANGE,
	COLOR_OUT_OF_RANGE,
	NO_CAMERA,
	TOO_MUCH_CAMERA,
	TOO_MUCH_AMBIENT_LIGHT,
	WRONG_ARGUMENT_COUNT,
	ERROR_COUNT
}			t_error_types;

# define DEFAULT_ERROR_MSG "Error\n"

# define INTENSITY_OUT_OF_RANGE_MSG "intensity value not in range [0.0, 1.0]"
# define COLOR_OUT_OF_RANGE_MSG "color value not in range [0, 255]"
# define NO_CAMERA_MSG "a scene need a camera to be rendered"
# define TOO_MUCH_CAMERA_MSG "a scene can only have one camera"
# define TOO_MUCH_AMBIENT_LIGHT_MSG "a scene can only have one ambient light"
# define WRONG_ARGUMENT_COUNT_MSG "wrong argument count"

char	**get_error_msgs(void);
void	rt_perror(char *caller_name, int error_type);

#endif
