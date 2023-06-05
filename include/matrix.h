/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 23:58:38 by suchua            #+#    #+#             */
/*   Updated: 2023/06/02 23:46:23 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "vector.h"

typedef struct s_mat
{
	t_vec	r1;
	t_vec	r2;
	t_vec	r3;
}	t_mat;

t_mat	get_transformation_mat(t_vec cam_dir);
t_vec	mat_transform(t_mat transform, t_vec v);
t_mat	new_mat(t_vec v1, t_vec v2, t_vec v3);
t_mat	mat_transposition(t_mat mat);

#endif
