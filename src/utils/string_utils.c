/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:18:16 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/28 15:19:31 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Returns the length of the NULL-terminated string array arr
 *
 * @param arr
 * @return int
 */
int	get_length(char **arr)
{
	int	count;

	count = 0;
	while (arr[count])
		count++;
	return (count);
}
