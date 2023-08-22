/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xyz.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 03:48:54 by suchua            #+#    #+#             */
/*   Updated: 2023/08/22 16:33:38 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transformation.h"

t_vec3	get_up(t_obj *selected, t_mat4 view_mat)
{
	t_vec3	right;
	t_vec3	forward;
	t_vec3	up;

	if (!selected)
		return (get_cam_up(view_mat));
	forward = normalize(selected->dir);
	if (vec3_dot(forward, new_vec3(0, 1, 0)))
		right = normalize(vec3_cross(forward, new_vec3(0, 0, 1)));
	else
		right = normalize(vec3_cross(forward, new_vec3(0, 1, 0)));
	up = normalize(vec3_cross(forward, right));
	return (up);
}

t_vec3	get_right(t_obj *selected, t_mat4 view_mat)
{
	t_vec3	right;
	t_vec3	forward;

	if (!selected)
		return (get_cam_right(view_mat));
	forward = normalize(selected->dir);
	if (vec3_dot(forward, new_vec3(0, 1, 0)))
		right = normalize(vec3_cross(forward, new_vec3(0, 0, 1)));
	else
		right = normalize(vec3_cross(forward, new_vec3(0, 1, 0)));
	return (right);
}

t_vec3	get_forward(t_obj *selected, t_mat4 view_mat)
{
	if (!selected)
		return (get_cam_forward(view_mat));
	return (selected->dir);
}
