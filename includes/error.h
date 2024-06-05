/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:32:45 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/05 15:43:49 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef enum e_error_types
{
	WRONG_PROGRAM_ARGUMENT,
	INTENSITY_OUT_OF_RANGE,
	COLOR_OUT_OF_RANGE,
	FOV_OUT_OF_RANGE,
	DIAMETER_OUT_OF_RANGE,
	WIDTH_OUT_OF_RANGE,
	HEIGHT_OUT_OF_RANGE,
	REFL_OUT_OF_RANGE,
	NO_CAMERA,
	TOO_MUCH_CAMERA,
	TOO_MUCH_AMBIENT_LIGHT,
	WRONG_ARGUMENT_COUNT,
	ERROR_COUNT
}			t_error_types;

# define DEFAULT_ERROR_MSG "Error\n"

# define WRONG_PROGRAM_ARGUMENT_MSG "the program requires 1 and only 1 \
.rt scene file as argument"
# define INTENSITY_OUT_OF_RANGE_MSG "intensity value not in range [0.0, 1.0]"
# define COLOR_OUT_OF_RANGE_MSG "color value not in range [0, 255]"
# define FOV_OUT_OF_RANGE_MSG "fov value not in range [0, 180]"
# define DIAMETER_OUT_OF_RANGE_MSG "diameter value not in range [0, +inf["
# define WIDTH_OUT_OF_RANGE_MSG "width value not in range [0, +inf["
# define HEIGHT_OUT_OF_RANGE_MSG "height value not in range [0, +inf["
# define REFL_OUT_OF_RANGE_MSG "reflectiveness value not in range [0.0, 1.0]"
# define NO_CAMERA_MSG "a scene needs a camera to be rendered"
# define TOO_MUCH_CAMERA_MSG "a scene can only have one camera"
# define TOO_MUCH_AMBIENT_LIGHT_MSG "a scene can only have one ambient light"
# define WRONG_ARGUMENT_COUNT_MSG "wrong argument count"

char	**get_error_msgs(void);
void	rt_perror(char *caller_name, int error_type);

#endif
