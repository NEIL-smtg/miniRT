/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 23:43:05 by suchua            #+#    #+#             */
/*   Updated: 2023/07/27 23:01:56 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// q = (w, x, y, z)
// q* = (w, -x, -y, -z)
t_quat	get_quaternion(double rad, t_vec3 dir)
{
	t_quat	q;
	double	c;
	double	s;

	c = cos(rad / 2);
	s = sin(rad / 2);
	q.quaternion = vec4_from_vec3(vec3_mul(s, dir), c);
	q.conjugate = vec4_mul(-1.0f, q.quaternion);
	q.conjugate.w *= -1.0f;
	return (q);
}

static t_vec4	qmul(t_vec4 a, t_vec4 b)
{
	t_vec4	res;

	res.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
	res.x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y;
	res.y = a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x;
	res.z = a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w;
	return (res);
}

//	p' = qpq*
t_vec3	rotate(t_vec3 pt, t_quat q)
{
	t_vec4	p;

	p = vec4_from_vec3(pt, 1);
	p = qmul(qmul(q.quaternion, p), q.conjugate);
	return (vec3_from_vec4(p));
}
