/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a4_mul.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 22:20:23 by suchua            #+#    #+#             */
/*   Updated: 2023/06/27 02:38:02 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_vec4	mat44_mul_mat41(t_mat4 a, t_vec4 v)
{
	t_vec4	res;

	res.x = a.r1.x * v.x + a.r1.y * v.y + a.r1.z * v.z + a.r1.w * v.w;
	res.y = a.r2.x * v.x + a.r2.y * v.y + a.r2.z * v.z + a.r2.w * v.w;
	res.z = a.r3.x * v.x + a.r3.y * v.y + a.r3.z * v.z + a.r3.w * v.w;
	res.w = a.r4.x * v.x + a.r4.y * v.y + a.r4.z * v.z + a.r4.w * v.w;
	return (res);
}

t_mat4	mat44_mul_mat44(t_mat4 a, t_mat4 b)
{
	t_mat4	res;

	b = mat4_transposition(b);
	res.r1.x = vec4_dot(a.r1, b.r1);
	res.r1.y = vec4_dot(a.r1, b.r2);
	res.r1.z = vec4_dot(a.r1, b.r3);
	res.r1.w = vec4_dot(a.r1, b.r4);
	res.r2.x = vec4_dot(a.r2, b.r1);
	res.r2.y = vec4_dot(a.r2, b.r2);
	res.r2.z = vec4_dot(a.r2, b.r3);
	res.r2.w = vec4_dot(a.r2, b.r4);
	res.r3.x = vec4_dot(a.r3, b.r1);
	res.r3.y = vec4_dot(a.r3, b.r2);
	res.r3.z = vec4_dot(a.r3, b.r3);
	res.r3.w = vec4_dot(a.r3, b.r4);
	res.r4.x = vec4_dot(a.r4, b.r1);
	res.r4.y = vec4_dot(a.r4, b.r2);
	res.r4.z = vec4_dot(a.r4, b.r3);
	res.r4.w = vec4_dot(a.r4, b.r4);
	return (res);
}
