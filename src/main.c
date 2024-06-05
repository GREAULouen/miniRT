/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:53:58 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/05 16:29:46 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// void	leaks(void)
// {
// 	system("leaks miniRT");
// 	atexit(leaks);
// }

int	main(int argc, char *argv[])
{
	if (argc != 2 || !ft_endswith(argv[1], ".rt"))
	{
		rt_perror((char *)__func__, WRONG_PROGRAM_ARGUMENT);
		exit(EXIT_FAILURE);
	}
	get_program()->file_name = argv[1];
	set_width_height(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	if (parse_input() < 0)
		exit(EXIT_FAILURE);
	if (!start_mlx())
	{
		cleanup_program();
		exit(EXIT_FAILURE);
	}
	cleanup_program();
	exit(EXIT_SUCCESS);
}
