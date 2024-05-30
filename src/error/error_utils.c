/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:31:47 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/30 14:16:50 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

char	**get_error_msgs(void)
{
	static char	*error_msgs[ERROR_COUNT];

	error_msgs[INTENSITY_OUT_OF_RANGE] = INTENSITY_OUT_OF_RANGE_MSG;
	error_msgs[COLOR_OUT_OF_RANGE] = COLOR_OUT_OF_RANGE_MSG;
	error_msgs[FOV_OUT_OF_RANGE] = FOV_OUT_OF_RANGE_MSG;
	error_msgs[DIAMETER_OUT_OF_RANGE] = DIAMETER_OUT_OF_RANGE_MSG;
	error_msgs[HEIGHT_OUT_OF_RANGE] = HEIGHT_OUT_OF_RANGE_MSG;
	error_msgs[NO_CAMERA] = NO_CAMERA_MSG;
	error_msgs[TOO_MUCH_CAMERA] = TOO_MUCH_CAMERA_MSG;
	error_msgs[TOO_MUCH_AMBIENT_LIGHT] = TOO_MUCH_AMBIENT_LIGHT_MSG;
	error_msgs[WRONG_ARGUMENT_COUNT] = WRONG_ARGUMENT_COUNT_MSG;
	return (&error_msgs[0]);
}

void	rt_perror(char *caller_name, int error_type)
{
	printf("%s", DEFAULT_ERROR_MSG);
	printf("%s: %s: %s\n", PROGRAM_NAME, caller_name, get_error_msgs()[error_type]);
}
