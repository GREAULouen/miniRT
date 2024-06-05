/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endswith.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:51:31 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/14 15:13:57 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/**
 * @brief Returns whether or not the seq is found at the end of src
 *
 * @param src
 * @param seq
 * @return int
 */
int	ft_endswith(char *src, char *seq)
{
	char	*start;

	if (!src || !seq)
		return (set_error((char *)__func__, INVALID_ARG), -1);
	if (!seq[0])
		return (1);
	start = ft_strrchr(src, seq[0]);
	if (!start || ft_strlen(start) != ft_strlen(seq))
		return (0);
	return (ft_strncmp(start, seq, ft_strlen(seq)) == 0);
}
