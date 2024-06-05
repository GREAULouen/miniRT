/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 07:44:42 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/05 16:45:33 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"

void	set_error(char *caller_name, int ft_errno)
{
	int	old_errno;

	set_error_caller(caller_name);
	old_errno = *get_errno();
	set_errno(ft_errno);
	if (old_errno != *get_errno())
		printf("%s%s: %s\n", "miniRT: ", *get_error_caller(),
			ft_strerror(*get_errno()));
}
