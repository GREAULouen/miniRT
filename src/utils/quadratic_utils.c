/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:44:08 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/30 17:48:59 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Solves ax^2 + bx + c = 0 and stores the solutions in sol.
 * Returns the number of solutions. (never 1 because of double imprecision)
 *
 * @param a
 * @param b
 * @param c
 * @param sol
 * @return int
 */
int	solve_quadratic(double a, double b, double c, int sol[2])
{
	double	delta;

	delta = b * b - 4.0 * a * c;
	if (delta < 0)
		return (0);
	delta = sqrt(delta);
	b *= -1.0;
	sol[0] = (b - delta) / (2.0 * a);
	sol[1] = (b + delta) / (2.0 * a);
	return (2);
}
