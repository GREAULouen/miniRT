/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:31:47 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/05 15:43:57 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

char	**get_error_msgs(void)
{
	static char	*error_msgs[ERROR_COUNT];

	error_msgs[WRONG_PROGRAM_ARGUMENT] = WRONG_PROGRAM_ARGUMENT_MSG;
	error_msgs[INTENSITY_OUT_OF_RANGE] = INTENSITY_OUT_OF_RANGE_MSG;
	error_msgs[COLOR_OUT_OF_RANGE] = COLOR_OUT_OF_RANGE_MSG;
	error_msgs[FOV_OUT_OF_RANGE] = FOV_OUT_OF_RANGE_MSG;
	error_msgs[DIAMETER_OUT_OF_RANGE] = DIAMETER_OUT_OF_RANGE_MSG;
	error_msgs[WIDTH_OUT_OF_RANGE] = WIDTH_OUT_OF_RANGE_MSG;
	error_msgs[HEIGHT_OUT_OF_RANGE] = HEIGHT_OUT_OF_RANGE_MSG;
	error_msgs[REFL_OUT_OF_RANGE] = REFL_OUT_OF_RANGE_MSG;
	error_msgs[NO_CAMERA] = NO_CAMERA_MSG;
	error_msgs[TOO_MUCH_CAMERA] = TOO_MUCH_CAMERA_MSG;
	error_msgs[TOO_MUCH_AMBIENT_LIGHT] = TOO_MUCH_AMBIENT_LIGHT_MSG;
	error_msgs[WRONG_ARGUMENT_COUNT] = WRONG_ARGUMENT_COUNT_MSG;
	return (&error_msgs[0]);
}

void	rt_perror(char *caller_name, int error_type)
{
	ft_putstr_fd(DEFAULT_ERROR_MSG, 2);
	ft_putstr_fd(PROGRAM_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(caller_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(get_error_msgs()[error_type], 2);
	ft_putchar_fd('\n', 2);
}
