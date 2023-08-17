/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xyz.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 03:48:54 by suchua            #+#    #+#             */
/*   Updated: 2023/08/18 00:25:39 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	t_vec3	up;

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
	t_vec3	forward;

	if (!selected)
		return (get_cam_forward(view_mat));
	return (selected->dir);
}

int	angle_handler(int keycode, t_obj *selected)
{
	t_vec3	n;
	int		angle;

	if (keycode % 2 == 0)
		angle = -ANGLE_ROTATION;
	else
		angle = ANGLE_ROTATION;
	if (selected)
	{
		n = selected->dir;
		if (keycode == KEY_THREE && n.y < 0.0)
			angle *= -1;
		else if (keycode == KEY_FOUR && n.y < 0.0)
			angle *= -1;
	}
	return (angle);
}

t_vec3	get_rotation_axis(int keycode, t_viewport *vp, int *angle)
{
	*angle = angle_handler(keycode, vp->selected);
	if (keycode == KEY_ONE || keycode == KEY_TWO)
	{
		printf("\nROTATING in X-AXIS\n");
		return (get_up(vp->selected, vp->view_mat));
	}
	else if (keycode == KEY_THREE || keycode == KEY_FOUR)
	{
		printf("\nROTATING in Y-AXIS\n");
		return (get_right(vp->selected, vp->view_mat));
	}
	else
	{
		printf("\nROTATING in Z-AXIS\n");
		return (get_forward(vp->selected, vp->view_mat));
	}
}
