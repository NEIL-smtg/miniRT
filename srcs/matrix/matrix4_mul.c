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

t_vec4	mat4_mul(t_mat4 a, t_vec4 v)
{
	t_vec4	res;

	res.x = a.r1.x * v.x + a.r1.y * v.y + a.r1.z * v.z + a.r1.w * v.w;
	res.y = a.r2.x * v.x + a.r2.y * v.y + a.r2.z * v.z + a.r2.w * v.w;
	res.z = a.r3.x * v.x + a.r3.y * v.y + a.r3.z * v.z + a.r3.w * v.w;
	res.w = a.r4.x * v.x + a.r4.y * v.y + a.r4.z * v.z + a.r4.w * v.w;
	return (res);
}
