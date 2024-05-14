/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:15:03 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/14 14:47:04 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_input(void)
{
	t_program	*program;

	program = get_program();
	printf("program state:\n");
	printf("  |- file_name: %s\n", program->file_name);
}
