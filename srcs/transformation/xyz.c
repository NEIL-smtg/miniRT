/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xyz.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 03:48:54 by suchua            #+#    #+#             */
/*   Updated: 2023/08/11 02:25:52 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transformation.h"

t_vec3	get_up(t_obj *selected, t_mat4 view_mat)
{
	t_vec3	right;

	if (!selected)
		return (get_cam_up(view_mat));
	if (fabs(selected->dir.x) == 1.0)
		right = new_vec3(0, 1, 0);
	else
		right = new_vec3(1, 0, 0);
	return (normalize(vec3_cross(selected->dir, right)));
}

t_vec3	get_right(t_obj *selected, t_mat4 view_mat)
{
	t_vec3	up;

	if (!selected)
		return (get_cam_right(view_mat));
	if (fabs(selected->dir.y) == 1.0)
		up = new_vec3(0, 0, -selected->dir.y);
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
