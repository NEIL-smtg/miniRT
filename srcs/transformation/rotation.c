/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 01:43:56 by suchua            #+#    #+#             */
/*   Updated: 2023/07/24 02:44:29 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_mat4	get_x_rotation_mat(double theta)
{
	t_mat4	rot;

	rot.r1 = new_vec4(1, 0, 0 ,0);
	rot.r2 = new_vec4(0, cos(theta), -sin(theta), 0);
	rot.r3 = new_vec4(0, sin(theta), cos(theta), 0);
	rot.r4 = new_vec4(0, 0, 0, 1);
	return (rot);
}

t_mat4	get_y_rotation_mat(double theta)
{
	t_mat4	rot;

	rot.r1 = new_vec4(cos(theta), 0, -sin(theta) ,0);
	rot.r2 = new_vec4(0, 1, 0, 0);
	rot.r3 = new_vec4(sin(theta), 0, cos(theta), 0);
	rot.r4 = new_vec4(0, 0, 0, 1);
	return (rot);
}

t_vec3	get_cam_up(t_mat4 view_mat)
{
	view_mat = mat4_transposition(view_mat);
	return (vec3_from_vec4(view_mat.r2));
}
