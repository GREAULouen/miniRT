/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_extract_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:48:42 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/23 18:55:04 by lgreau           ###   ########.fr       */
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
