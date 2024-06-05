/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector3.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:30:28 by lgreau            #+#    #+#             */
/*   Updated: 2024/05/21 12:19:19 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR3_H
# define FT_VECTOR3_H

# include "../ft_error/ft_error.h"
# include <stdlib.h> // malloc
# include <math.h>	// cos, sin

# define DEFAULT 0
# define ONELINE 1

typedef struct s_vector3
{
	double	x;
	double	y;
	double	z;
}				t_vector3;

double			ft_dot_product(t_vector3 *v1, t_vector3 *v2);

t_vector3		*ft_v3_add(t_vector3 *v1, t_vector3 *v2);
t_vector3		*ft_v3_sub(t_vector3 *v1, t_vector3 *v2);
t_vector3		*ft_v3_mult(t_vector3 *v1, double coef);
t_vector3		*ft_v3_div(t_vector3 *v1, double coef);

void			ft_v3_inadd(t_vector3 *v1, t_vector3 *v2);
void			ft_v3_insub(t_vector3 *v1, t_vector3 *v2);
void			ft_v3_inmult(t_vector3 *v1, double coef);
void			ft_v3_indiv(t_vector3 *v1, double coef);

void			print_v3(char *prefix, t_vector3	*v, int format);

t_vector3		*ft_v3_zero(void);
t_vector3		*ft_v3_new(double x, double y, double z);
t_vector3		*ft_v3_cpy(t_vector3 *v);
t_vector3		*ft_v3_dir(t_vector3 *v1, t_vector3 *v2);

void			ft_inrotate_x(t_vector3 *v, double theta);
void			ft_inrotate_y(t_vector3 *v, double theta);
void			ft_inrotate_z(t_vector3 *v, double theta);

#endif
