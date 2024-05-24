/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:46:49 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/24 10:39:52 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Calculates k * (RGB) = kR, kG, kB.
 * Keeping the result in range 0-255.
 *
 * @param color
 * @param k can be negative to get RGB = 000;
 * @return uint32_t
 */
uint32_t	color_k_mult(uint32_t color, int k)
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
