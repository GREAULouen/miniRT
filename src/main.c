/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:53:58 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/22 14:04:08 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char *argv[])
{
	if (argc != 2 || !ft_endswith(argv[1], ".rt"))
	{
		write(2, BAD_ARGS_FORMAT, ft_strlen(BAD_ARGS_FORMAT));
		exit(EXIT_FAILURE);
	}
	get_program()->file_name = argv[1];
	get_program()->screen_width = DEFAULT_WIDTH;
	get_program()->screen_height = DEFAULT_HEIGHT;
	parse_input();
	// TODO : clean the program structure
	exit(EXIT_SUCCESS);
}