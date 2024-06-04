/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:53:58 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/04 14:09:39 by lgreau           ###   ########.fr       */
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
	// TODO : clean the program structure
	cleanup_program();

	// (void)argc;
	// (void)argv;


	// t_matrix	rot;
	// t_vector3	dir = (t_vector3){0.000000, -0.382683, 0.923880};
	// ft_v3_innormalize(&dir);

	// ft_rotation_matrix(&dir, &rot);

	// t_vector3	input = (t_vector3){0.0, 0.0, 1.0};
	// t_vector3	res = (t_vector3){0.0, 0.0, 0.0};

	// ft_apply_rotate(&input, &rot, &res);
	// print_v3("Before, ", &input, ONELINE);
	// print_v3(" > After", &res, ONELINE);

	// printf("\n");

	// input = (t_vector3){1.0, 0.0, 0.0};
	// ft_apply_rotate(&input, &rot, &res);
	// print_v3("Before, ", &input, ONELINE);
	// print_v3(" > After", &res, ONELINE);

	// printf("\n");

	// input = (t_vector3){1.0, 1.0, 1.0};
	// ft_apply_rotate(&input, &rot, &res);
	// print_v3("Before, ", &input, ONELINE);
	// print_v3(" > After", &res, ONELINE);

	exit(EXIT_SUCCESS);
}
