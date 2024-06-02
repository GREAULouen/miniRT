/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:45:18 by pgrossma          #+#    #+#             */
/*   Updated: 2024/06/02 16:16:35 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	(void) param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(get_program()->mlx);
	if (keydata.key == MLX_KEY_R)
		get_program()->image_count = 0;
}
