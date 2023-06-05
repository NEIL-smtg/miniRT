/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 23:58:03 by suchua            #+#    #+#             */
/*   Updated: 2023/06/05 02:14:29 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_mat	new_mat(t_vec v1, t_vec v2, t_vec v3)
{
	t_mat	new;

	new.r1 = new_vec(v1.x, v1.y, v1.z);
	new.r2 = new_vec(v2.x, v2.y, v2.z);
	new.r3 = new_vec(v3.x, v3.y, v3.z);
	return (new);
}

t_mat	mat_transposition(t_mat mat)
{
	t_mat	new;

	new.r1 = new_vec(new.r1.x, new.r2.x, new.r3.x);
	new.r2 = new_vec(new.r1.y, new.r2.y, new.r3.y);
	new.r3 = new_vec(new.r1.z, new.r2.z, new.r3.z);
	return (new);
}

// t_mat	get_transformation_mat(t_vec cam_dir)
// {
// 	t_vec	u;
// 	t_vec	w;
// 	t_vec	v;
// 	t_mat	mat;

// 	w = normalize(cam_dir);
// 	u = new_vec(w.z, 0, -w.x);
// 	if (normalize_divisor(u) == 0)
// 		u = new_vec(-w.y, w.x, 0);
// 	u = normalize(u);
// 	v = cross_product(w, u);
// 	mat = new_mat(u, v, w);
// 	return (mat_transposition(mat));
// }

t_mat	get_transformation_mat(t_vec cam_dir)
{
	t_vec	u;
	t_vec	v;
	t_vec	w;
	t_mat	mat;

	w = normalize(cam_dir);
	u = new_vec(0, 1, 0);
	if (1.0 == w.z)
		v = new_vec(1, 0, 0);
	else if (-1.0 == w.z)
		v = new_vec(-1, 0, 0);
	else
	{
		u = new_vec(w.y, -w.x, 0);
		u = normalize(u);
		v = cross_product(w, u);
	}
	mat = new_mat(u, v, w);
	return (mat_transposition(mat));
}

t_vec	mat_transform(t_mat transform, t_vec v)
{
	t_vec	new;
	t_mat	a;

	a = mat_transposition(transform);
	new.x = dot_product(a.r1, v);
	new.y = dot_product(a.r2, v);
	new.z = dot_product(a.r3, v);
	return (new);
}
