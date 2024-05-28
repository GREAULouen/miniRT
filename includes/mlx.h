/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:55:20 by pgrossma          #+#    #+#             */
/*   Updated: 2024/05/28 14:42:17 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_H
# define MLX_H

# define DEFAULT_WIDTH 1280
# define DEFAULT_HEIGHT 720

void	start_mlx(void);
void	resize_hook(int32_t width, int32_t height, void *param);
void	set_width_height(int32_t width, int32_t height);

#endif