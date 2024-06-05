/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v3_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:07:14 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/14 13:15:10 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector3.h"

/**
 * @brief Prints the given t_vector3 in ONELINE (x, y, z)
 *
 * @param v
 * @param format
 */
void	print_v3(char *prefix, t_vector3	*v, int format)
{
	printf("%s", prefix);
	if (format == ONELINE)
		printf(": (%f, %f, %f)\n", v->x, v->y, v->z);
	else
	{
		printf(" coordinates:\n");
		printf("  |- x: %f\n", v->x);
		printf("  |- y: %f\n", v->y);
		printf("  |- z: %f\n", v->z);
	}
}
