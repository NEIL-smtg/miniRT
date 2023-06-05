/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:00:07 by suchua            #+#    #+#             */
/*   Updated: 2023/06/02 23:32:10 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <stdio.h>

void	print_vector(t_vec v, char *name)
{
	printf("%s = %f %f %f\n", name, v.x, v.y, v.z);
}

double	get_radian(int angle)
{
	return ((double) angle * M_PI / 180);
}

t_vec	vec_mul(double scalar, t_vec v)
{
	return (new_vec(
			scalar * v.x,
			scalar * v.y,
			scalar * v.z
		));
}

t_vec	cross_product(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}
