/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:41:28 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/14 16:47:16 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Frees every string in arr until either last or NULL and then frees
 * arr itself if is_allocated
 *
 * @param arr
 * @param last
 * @param is_allocated
 */
void	free_arr(char **arr, int last, int is_allocated)
{
	int	index;

	index = -1;
	if (!arr)
		return ;
	if (last < 0)
		while (arr[++index])
			free(arr[index]);
	else
		while (--last >= 0)
			if (arr[last])
				free(arr[last]);
	if (is_allocated)
		free(arr);
}
