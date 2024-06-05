/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bitmap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 09:43:01 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/05 15:44:41 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BITMAP_H
# define FT_BITMAP_H

# include "../ft_error/ft_error.h" // ft_errno

# include <stdint.h> // uint32_t linux
# include <stdlib.h> // uint32_t
# include <stdarg.h> // va_arg

# define MAX_BITS 32

// u_int32_t: for linux
// uint32_t: for MAC
typedef struct s_bitmap
{
	uint32_t	bits;
}			t_bitmap;

uint32_t	ft_mask(int len, ...);

#endif
