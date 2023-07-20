/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 02:04:33 by suchua            #+#    #+#             */
/*   Updated: 2023/07/21 02:30:51 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	new_vec3(double x, double y, double z)
{
	t_vec3	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_vec4	new_vec4(double x, double y, double z, double w)
{
	t_vec4	new;

	new.x = x;
	new.y = y;
	new.z = z;
	new.w = w;
	return (new);
}

double	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	double	x;
	double	y;
	double	z;

	x = v1.x * v2.x;
	y = v1.y * v2.y;
	z = v1.z * v2.z;
	return (x + y + z);
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

double	vec3_len(t_vec3 v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

t_vec3	normalize(t_vec3 vec)
{
	double	dir_len;

	dir_len = vec3_len(vec);
	return (new_vec3(
			vec.x / dir_len,
			vec.y / dir_len,
			vec.z / dir_len
		));
}
