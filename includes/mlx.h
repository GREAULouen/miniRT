/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:55:20 by pgrossma          #+#    #+#             */
/*   Updated: 2024/06/02 15:22:58 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_H
# define MLX_H

# define DEFAULT_WIDTH 1280
# define DEFAULT_HEIGHT 720

/* ~~~~ Main structure ~~~~	*/
bool	start_mlx(void);
bool	start_img_buffer(void);

/* ~~~~~~~~~ Hooks ~~~~~~~~~*/
void	resize_hook(int32_t width, int32_t height, void *param);
void	set_width_height(int32_t width, int32_t height);
void	key_hook(mlx_key_data_t keydata, void *param);
void	loop_hook(void *param);

/* ~~~~~~~~~ Utils ~~~~~~~~~*/
bool	mlx_print_error(void);

#endif