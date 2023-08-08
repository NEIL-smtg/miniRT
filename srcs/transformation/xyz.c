/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xyz.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 03:48:54 by suchua            #+#    #+#             */
/*   Updated: 2023/08/09 03:54:15 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transformation.h"

t_vec3	get_up(t_obj *selected, t_mat4 view_mat)
{
	t_vec3	right;

	if (!selected)
		return (get_cam_up(view_mat));
	if (selected->dir.y <= EPS)
		right = new_vec3(-1, 0, 0);
	else
		right = new_vec3(1, 0, 0);
	return (normalize(vec3_cross(selected->dir, right)));
}

t_vec3	get_right(t_obj *selected, t_mat4 view_mat)
{
	t_vec3	up;

	if (!selected)
		return (get_cam_up(view_mat));
	if (selected->dir.x <= EPS)
		up = new_vec3(0, -1, 0);
	else
		up = new_vec3(0, 1, 0);
	return (normalize(vec3_cross(selected->dir, up)));
}

t_vec3	get_forward(t_obj *selected, t_mat4 view_mat)
{
	t_vec3	forward;

	if (!selected)
		return (get_cam_forward(view_mat));
	return (selected->dir);
}
