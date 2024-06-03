/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_extract_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:48:42 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/02 16:13:01 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Get the red component stored in color
 *
 * @param color formatted like : XXRRGGBB
 * @return uint32_t 000000RR
 */
uint32_t	get_red(uint32_t color)
{
	return ((color >> 16) & 0xFF);
}

/**
 * @brief Get the green component stored in color
 *
 * @param color formatted like : XXRRGGBB
 * @return uint32_t 000000GG
 */
uint32_t	get_green(uint32_t color)
{
	return ((color >> 8) & 0xFF);
}

/**
 * @brief Get the blue component stored in color
 *
 * @param color formatted like : XXRRGGBB
 * @return uint32_t 000000BB
 */
uint32_t	get_blue(uint32_t color)
{
	return (color & 0xFF);
}

uint32_t	color_clamp(uint32_t color)
{
	uint32_t	final_color;
	uint32_t	red;
	uint32_t	green;
	uint32_t	blue;

	final_color = 0x0;
	red = get_red(color);
	green = get_green(color);
	blue = get_blue(color);
	final_color |= ((red * (red > 0 && red < 256) + 255 * (red > 255)) << 16);
	final_color |= ((green * (green > 0 && green < 256) + 255 * (green > 255)) << 8);
	final_color |= (blue * (blue > 0 && blue < 256) + 255 * (blue > 255));
	return (final_color);
}
