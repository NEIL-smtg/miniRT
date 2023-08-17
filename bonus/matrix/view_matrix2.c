/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_matrix2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 00:04:24 by suchua            #+#    #+#             */
/*   Updated: 2023/07/26 00:04:29 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_vec3	get_cam_right(t_mat4 view_mat)
{
	view_mat = mat4_transposition(view_mat);
	return (vec3_from_vec4(view_mat.r1));
}

t_vec3	get_cam_up(t_mat4 view_mat)
{
	view_mat = mat4_transposition(view_mat);
	return (vec3_from_vec4(view_mat.r2));
}

t_vec3	get_cam_forward(t_mat4 view_mat)
{
	view_mat = mat4_transposition(view_mat);
	return (vec3_from_vec4(view_mat.r3));
}
