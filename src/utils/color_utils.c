/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:46:49 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/28 12:42:14 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Calculates & returns C1 - C2 clamped to [0; 255]
 *
 * @param color1
 * @param color2
 * @return uint32_t
 */
uint32_t	color_sub(uint32_t color1, uint32_t color2)
{
	uint32_t	new_color2;
	int			tmp;

	new_color2 = 0;
	tmp = get_red(color1) - get_red(color2);
	new_color2 = ((255 * (tmp > 255) + tmp * (tmp <= 255 && tmp >= 0)) << 16);
	tmp = get_green(color1) - get_green(color2);
	new_color2 |= ((255 * (tmp > 255) + tmp * (tmp <= 255 && tmp >= 0)) << 8);
	tmp = get_blue(color1) - get_blue(color2);
	new_color2 |= ((255 * (tmp > 255) + tmp * (tmp <= 255 && tmp >= 0)));
	return (new_color2);
}

/**
 * @brief Calculates k * (RGB) = kR, kG, kB.
 * Keeping the result in range 0-255.
 *
 * @param color
 * @param k can be negative to get RGB = 000;
 * @return uint32_t
 */
uint32_t	color_scal_mult(uint32_t color, double k)
{
	uint32_t	new_color;
	uint32_t	tmp;

	if (k < 0)
		return (0);
	tmp = get_red(color) * k;
	new_color = ((255 * (tmp > 255) + tmp * (tmp <= 255)) << 16);
	tmp = get_green(color) * k;
	new_color |= ((255 * (tmp > 255) + tmp * (tmp <= 255)) << 8);
	tmp = get_blue(color) * k;
	new_color |= (255 * (tmp > 255) + tmp * (tmp <= 255));
	return (new_color);
}

/**
 * @brief Returns R1, G1, B1 + R2, G2, B2 = R1 + R2, G1 + G2, B1 + B2
 *
 * @param color1
 * @param color2
 * @return uint32_t
 */
uint32_t	color_add(uint32_t color1, uint32_t color2)
{
	uint32_t	new_color;
	uint32_t	tmp;

	tmp = get_red(color1) + get_red(color2);
	new_color = ((255 * (tmp > 255) + tmp * (tmp <= 255)) << 16);
	tmp = get_green(color1) + get_green(color2);
	new_color |= ((255 * (tmp > 255) + tmp * (tmp <= 255)) << 8);
	tmp = get_blue(color1) + get_blue(color2);
	new_color |= (255 * (tmp > 255) + tmp * (tmp <= 255));
	return (new_color);
}

/**
 * @brief Returns C1 + k * C2
 *
 * @param color1
 * @param k
 * @param color2
 * @return uint32_t
 */
uint32_t	color_add_scal(uint32_t color1, double k, uint32_t color2)
{
	return (color_add(color1, color_scal_mult(color2, k)));
}

/**
 * @brief Calculates & returns C1 - (255 - C2)
 *
 * @param color1
 * @param color2
 * @return uint32_t
 */
uint32_t	color_rem_opposite(uint32_t color1, uint32_t color2)
{
	return (color_sub(color1, color_sub(0xFFFFFF, color2)));
}
