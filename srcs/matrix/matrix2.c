/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:40:33 by suchua            #+#    #+#             */
/*   Updated: 2023/07/06 02:08:37 by suchua           ###   ########.fr       */
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

t_mat4	mat4_transposition(t_mat4 m)
{
	t_mat4	new;

	new.r1 = new_vec4(m.r1.x, m.r2.x, m.r3.x, m.r4.x);
	new.r2 = new_vec4(m.r1.y, m.r2.y, m.r3.y, m.r4.y);
	new.r3 = new_vec4(m.r1.z, m.r2.z, m.r3.z, m.r4.z);
	new.r4 = new_vec4(m.r1.w, m.r2.w, m.r3.w, m.r4.w);
	return (new);
}
