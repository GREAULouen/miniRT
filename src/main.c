/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:53:58 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/28 14:54:50 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	leaks(void)
{
	system("leaks miniRT");
}

int	main(int argc, char *argv[])
{
	atexit(leaks);
	if (argc != 2 || !ft_endswith(argv[1], ".rt"))
	{
		write(2, BAD_ARGS_FORMAT, ft_strlen(BAD_ARGS_FORMAT));
		exit(EXIT_FAILURE);
	}
	get_program()->file_name = argv[1];
	set_width_height(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	parse_input();
	if (*get_errno() != NO_ERROR
		|| !start_mlx())
	{
		cleanup_program();
		exit(EXIT_FAILURE);
	}
	// TODO : clean the program structure
	cleanup_program();
	exit(EXIT_SUCCESS);
}