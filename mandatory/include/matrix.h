/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 23:58:38 by suchua            #+#    #+#             */
/*   Updated: 2023/08/22 16:35:39 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "vector.h"

typedef struct s_mat3
{
	t_vec3	r1;
	t_vec3	r2;
	t_vec3	r3;
}	t_mat3;

typedef struct s_mat4
{
	t_vec4	r1;
	t_vec4	r2;
	t_vec4	r3;
	t_vec4	r4;
}	t_mat4;

//create new matrix
t_mat3	new_mat3(t_vec3 v1, t_vec3 v2, t_vec3 v3);
t_mat4	new_mat4(t_vec4 v1, t_vec4 v2, t_vec4 v3, t_vec4 v4);
t_vec4	vec4_from_vec3(t_vec3 v, double x);

t_vec3	mat_transform(t_mat3 transform, t_vec3 v);
t_mat3	mat_transposition(t_mat3 mat);
t_mat4	mat4_transposition(t_mat4 m);

t_vec4	mat44_mul_mat41(t_mat4 a, t_vec4 v);
t_mat4	inverse_mat4(t_mat4 mat);

t_vec3	vec3_from_vec4(t_vec4 v);
t_vec3	mat33_mul_mat31(t_mat3 a, t_vec3 b);
t_mat4	mat44_mul_mat44(t_mat4 a, t_mat4 b);

//	rotation
t_vec3	get_cam_up(t_mat4 view_mat);
t_vec3	get_cam_forward(t_mat4 view_mat);
t_vec3	get_cam_right(t_mat4 view_mat);

#endif
