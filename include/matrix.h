/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 23:58:38 by suchua            #+#    #+#             */
/*   Updated: 2023/05/24 23:59:55 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_mat
{
	t_vec	r1;
	t_vec	r2;
	t_vec	r3;
}	t_mat;

t_vec	cross_product(t_vec a, t_vec b);
t_mat	new_mat(t_vec v1, t_vec v2, t_vec v3);
t_mat	mat_transposition(t_mat mat);

#endif
