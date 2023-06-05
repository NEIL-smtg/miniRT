/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 02:04:33 by suchua            #+#    #+#             */
/*   Updated: 2023/06/02 23:30:32 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec	new_vec(double x, double y, double z)
{
	t_vec	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

double	dot_product(t_vec v1, t_vec v2)
{
	double	x;
	double	y;
	double	z;

	x = v1.x * v2.x;
	y = v1.y * v2.y;
	z = v1.z * v2.z;
	return (x + y + z);
}

double	normalize_divisor(t_vec v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

t_vec	normalize(t_vec vec)
{
	double	dir_len;

	dir_len = normalize_divisor(vec);
	return (new_vec(
			vec.x / dir_len,
			vec.y / dir_len,
			vec.z / dir_len
		));
}
