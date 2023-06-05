/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 23:06:34 by suchua            #+#    #+#             */
/*   Updated: 2023/06/02 23:31:22 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# ifndef M_PI
#  define M_PI	3.14159265358979323846
# endif

# include <math.h>

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vec;

//vector
t_vec		new_vec(double x, double y, double z);
double		dot_product(t_vec v1, t_vec v2);
t_vec		normalize(t_vec vec);
double		normalize_divisor(t_vec v);
void		print_vector(t_vec v, char *name);
double		get_radian(int angle);
t_vec		vec_mul(double scalar, t_vec v);
t_vec		cross_product(t_vec a, t_vec b);

#endif
