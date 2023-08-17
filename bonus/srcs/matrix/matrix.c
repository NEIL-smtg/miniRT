/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 23:58:03 by suchua            #+#    #+#             */
/*   Updated: 2023/07/27 23:01:08 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_mat3	new_mat3(t_vec3 v1, t_vec3 v2, t_vec3 v3)
{
	t_mat3	new;

	new.r1 = new_vec3(v1.x, v1.y, v1.z);
	new.r2 = new_vec3(v2.x, v2.y, v2.z);
	new.r3 = new_vec3(v3.x, v3.y, v3.z);
	return (new);
}

t_mat4	new_mat4(t_vec4 v1, t_vec4 v2, t_vec4 v3, t_vec4 v4)
{
	t_mat4	new;

	new.r1 = new_vec4(v1.x, v1.y, v1.z, v1.w);
	new.r2 = new_vec4(v2.x, v2.y, v2.z, v2.w);
	new.r3 = new_vec4(v3.x, v3.y, v3.z, v3.w);
	new.r4 = new_vec4(v4.x, v4.y, v4.z, v4.w);
	return (new);
}

t_mat3	mat_transposition(t_mat3 mat)
{
	t_mat3	new;

	new.r1 = new_vec3(mat.r1.x, mat.r2.x, mat.r3.x);
	new.r2 = new_vec3(mat.r1.y, mat.r2.y, mat.r3.y);
	new.r3 = new_vec3(mat.r1.z, mat.r2.z, mat.r3.z);
	return (new);
}

t_vec3	mat_transform(t_mat3 transform, t_vec3 v)
{
	t_vec3	new;
	t_mat3	a;

	a = mat_transposition(transform);
	new.x = vec3_dot(a.r1, v);
	new.y = vec3_dot(a.r2, v);
	new.z = vec3_dot(a.r3, v);
	return (new);
}
