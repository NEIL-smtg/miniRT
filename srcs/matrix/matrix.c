/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 23:58:03 by suchua            #+#    #+#             */
/*   Updated: 2023/05/24 23:58:28 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_vec	cross_product(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

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
