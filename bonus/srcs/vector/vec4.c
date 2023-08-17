/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:30:27 by suchua            #+#    #+#             */
/*   Updated: 2023/07/27 15:31:46 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec4	new_vec4(double x, double y, double z, double w)
{
	t_vec4	new;

	new.x = x;
	new.y = y;
	new.z = z;
	new.w = w;
	return (new);
}

double	vec4_dot(t_vec4 v1, t_vec4 v2)
{
	double	x;
	double	y;
	double	z;
	double	w;

	x = v1.x * v2.x;
	y = v1.y * v2.y;
	z = v1.z * v2.z;
	w = v1.w * v2.w;
	return (x + y + z + w);
}

double	vec4_len(t_vec4 v)
{
	double	res;

	res = pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2) + pow(v.w, 2);
	return (sqrt(res));
}

t_vec4	vec4_normalize(t_vec4 vec)
{
	double	dir_len;

	dir_len = vec4_len(vec);
	return (new_vec4(
			vec.x / dir_len,
			vec.y / dir_len,
			vec.z / dir_len,
			vec.w / dir_len
		));
}

t_vec4	vec4_mul(double scalar, t_vec4 v)
{
	return (new_vec4(
			scalar * v.x,
			scalar * v.y,
			scalar * v.z,
			scalar * v.w
		));
}
