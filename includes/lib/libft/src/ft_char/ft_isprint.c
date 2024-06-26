/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:43:31 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 12:36:02 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_char.h"

int	ft_isprint(int c)
{
	return (c >= SPACE && c <= 126);
}
