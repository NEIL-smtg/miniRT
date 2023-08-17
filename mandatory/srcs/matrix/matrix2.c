/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:40:33 by suchua            #+#    #+#             */
/*   Updated: 2023/07/27 22:56:09 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_vec4	vec4_from_vec3(t_vec3 v, double x)
{
	t_vec4	a;

	a.x = v.x;
	a.y = v.y;
	a.z = v.z;
	a.w = x;
	return (a);
}

t_vec3	vec3_from_vec4(t_vec4 v)
{
	t_vec3	new;

	new.x = v.x;
	new.y = v.y;
	new.z = v.z;
	return (new);
}

t_mat4	mat4_transposition(t_mat4 m)
{
	t_mat4	new;

	new.r1 = new_vec4(m.r1.x, m.r2.x, m.r3.x, m.r4.x);
	new.r2 = new_vec4(m.r1.y, m.r2.y, m.r3.y, m.r4.y);
	new.r3 = new_vec4(m.r1.z, m.r2.z, m.r3.z, m.r4.z);
	new.r4 = new_vec4(m.r1.w, m.r2.w, m.r3.w, m.r4.w);
	return (new);
}

t_vec3	mat33_mul_mat31(t_mat3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = b.x * a.r1.x + b.y * a.r1.y + b.z * a.r1.z;
	res.y = b.x * a.r2.x + b.y * a.r2.y + b.z * a.r2.z;
	res.z = b.x * a.r3.x + b.y * a.r3.y + b.z * a.r3.z;
	return (res);
}
