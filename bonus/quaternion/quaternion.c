/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 23:43:05 by suchua            #+#    #+#             */
/*   Updated: 2023/08/14 02:38:06 by suchua           ###   ########.fr       */
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
	q.quaternion = vec4_normalize(q.quaternion);
	q.conjugate = vec4_mul(-1.0, q.quaternion);
	q.conjugate.w *= -1.0;
	return (q);
}

t_vec4	qmul(t_vec4 a, t_vec4 b)
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

	p = vec4_from_vec3(pt, 0.0);
	p = qmul(qmul(q.quaternion, p), q.conjugate);
	return (vec3_from_vec4(p));
}

t_vec4	quaternion_euler(double x, double y, double z)
{
	t_vec3	rad;
	t_vec3	c;
	t_vec3	s;
	t_vec4	euler;

	rad.x = get_radian(x / 2);
	rad.y = get_radian(y / 2);
	rad.z = get_radian(z / 2);
	s.x = sin(rad.x);
	s.y = sin(rad.y);
	s.z = sin(rad.z);
	c.x = cos(rad.x);
	c.y = cos(rad.y);
	c.z = cos(rad.z);
	euler.w = c.x * c.y * c.z + s.x * s.y * s.z;
	euler.x = s.x * c.y * c.z - c.x * s.y * s.z;
	euler.y = c.x * s.y * c.z + s.x * c.y * s.z;
	euler.z = c.x * c.y * s.z - s.x * s.y * c.z;
	return (vec4_normalize(euler));
}
