/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:37:58 by suchua            #+#    #+#             */
/*   Updated: 2023/07/27 23:59:03 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	origin_translate(t_vec3 rot_center,
		enum e_rotation rot, t_obj *selected)
{
	t_vec3	translate;

	translate = rot_center;
	if (rot == to_origin)
		translate = vec3_mul(-1, rot_center);
	selected->center = vec3_add(selected->center, translate);
}

static void	quaternion_rotation(t_quat q, t_obj *selected)
{
	selected->center = rotate(selected->center, q);
	if (selected->type != SPHERE)
		selected->dir = normalize(rotate(selected->dir, q));
}

static t_vec3	get_rot_axis(int keycode, t_obj *selected, int *angle)
{
	t_vec3	x;

	if (keycode == KEY_ONE || keycode == KEY_THREE)
		*angle = -ANGLE_ROTATION;
	else if (keycode == KEY_TWO || keycode == KEY_FOUR)
		*angle = ANGLE_ROTATION;
	if (keycode == KEY_ONE || keycode == KEY_TWO)
		return (normalize(vec3_cross(selected->dir, new_vec3(0, 0, 1))));
	x = vec3_cross(selected->dir, new_vec3(0, 0, 1));
	x = normalize(vec3_cross(x, selected->dir));
	return (x);
}

static void	ft_obj_panning(int keycode, t_viewport *vp)
{
	t_quat	q;
	t_vec3	rot_center;
	t_vec3	rot_axis;
	int		angle;

	rot_axis = get_rot_axis(keycode, vp->selected, &angle);
	rot_center = vp->selected->center;
	origin_translate(rot_center, to_origin, vp->selected);
	q = get_quaternion(get_radian(angle), rot_axis);
	quaternion_rotation(q, vp->selected);
	origin_translate(rot_center, revert, vp->selected);
	render(vp, *vp->scene);
}

void	panning(int key, t_viewport *vp)
{
	if (!vp->selected)
		ft_cam_panning(key, vp);
	else if (vp->selected->type == SPHERE)
	{
		printf("\nSphere cannot be rotated !!\n");
		printf("Please choose CYLINDER or PLANE for rotation.\n\n");
		return ;
	}
	else
		ft_obj_panning(key, vp);
}
