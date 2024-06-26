/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswspace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 07:49:56 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/09 07:50:25 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iswspace(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}
