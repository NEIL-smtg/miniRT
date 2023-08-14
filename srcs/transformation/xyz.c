/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xyz.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 03:48:54 by suchua            #+#    #+#             */
/*   Updated: 2023/08/12 01:37:59 by suchua           ###   ########.fr       */
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
	// t_vec3	up;
	// t_vec3	world_up;
	// t_vec3	n;
	// double	dot;
	// world_right = new_vec3(1, 0, 0);
	// n = selected->dir;
	// dot = vec3_dot(n, world_right) > 0.99;
	// if (dot > 0.99)
	// 	right = new_vec3(0, 1, 0);
	// else
	// 	right = new_vec3(1, 0, 0);
	forward = normalize(selected->dir);
	if (fabs(forward.y) == 1.0)
		right = normalize(vec3_cross(forward, new_vec3(0, 0, forward.y)));
	else
		right = normalize(vec3_cross(forward, new_vec3(0, -1, 0)));
	up = normalize(vec3_cross(forward, right));
	return (up);
	// return (normalize(vec3_cross(right, n)));
}

t_vec3	get_right(t_obj *selected, t_mat4 view_mat)
{
	// t_vec3	up;
	// t_vec3	world_up;
	// t_vec3	n;
	// double	dot;

	if (!selected)
		return (get_cam_right(view_mat));
	// n = selected->dir;
	// world_up = new_vec3(0, 1, 0);
	// dot = vec3_dot(n, world_up);
	// if (dot > 0.99)
	// 	up = new_vec3(0, 0, 1);
	// else
	// 	up = new_vec3(0, 1, 0);
	// return (normalize(vec3_cross(up, n)));
	t_vec3	right;
	t_vec3	forward;
	t_vec3	up;
	forward = normalize(selected->dir);
	if (fabs(forward.y) == 1.0)
		right = normalize(vec3_cross(forward, new_vec3(0, 0, forward.y)));
	else
		right = normalize(vec3_cross(forward, new_vec3(0, -1, 0)));
	return (right);
}

t_vec3	get_forward(t_obj *selected, t_mat4 view_mat)
{
	t_vec3	forward;

	if (!selected)
		return (get_cam_forward(view_mat));
	return (selected->dir);
}
