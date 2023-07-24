/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:00:07 by suchua            #+#    #+#             */
/*   Updated: 2023/07/24 02:29:59 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <stdio.h>

void	print_vec3(t_vec3 v, char *name)
{
	printf("%s = %f %f %f\n", name, v.x, v.y, v.z);
}

double	get_radian(int angle)
{
	return ((double) angle * M_PI / 180);
}

t_vec3	vec3_mul(double scalar, t_vec3 v)
{
	return (new_vec3(
			scalar * v.x,
			scalar * v.y,
			scalar * v.z
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

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return (new_vec3(
			a.x - b.x,
			a.y - b.y,
			a.z - b.z
		));
}

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return (new_vec3(
			a.x + b.x,
			a.y + b.y,
			a.z + b.z
		));
}
