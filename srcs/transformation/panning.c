/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:37:58 by suchua            #+#    #+#             */
/*   Updated: 2023/08/02 17:34:20 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	get_rotation_axis(int keycode, t_viewport *vp, int *angle)
{
	if (keycode % 2 == 0)
		*angle = -ANGLE_ROTATION;
	else
		*angle = ANGLE_ROTATION;
	if (keycode == KEY_ONE || keycode == KEY_TWO)
	{
		printf("\nROTATING in X-AXIS\n");
		if (vp->selected)
			return (normalize(vec3_cross(vp->selected->dir,
						new_vec3(1, 0, 0))));
		return (get_cam_up(vp->view_mat));
	}
	else if (keycode == KEY_THREE || keycode == KEY_FOUR)
	{
		printf("\nROTATING in Y-AXIS\n");
		if (vp->selected)
			return (normalize(vec3_cross(vp->selected->dir,
						new_vec3(0, 1, 0))));
		return (get_cam_right(vp->view_mat));
	}
	else
	{
		printf("\nROTATING in Z-AXIS\n");
		if (vp->selected)
			return (vp->selected->dir);
		return (get_cam_forward(vp->view_mat));
	}
}

static void	origin_translation(t_viewport *vp, t_vec3 rot_center, \
	enum e_rotation rot)
{
	t_vec3	translate;
	t_obj	*obj;

	translate = rot_center;
	if (rot == to_origin)
		translate = vec3_mul(-1, rot_center);
	if (vp->selected)
	{
		vp->selected->center = translate;
		return ;
	}
	obj = vp->scene->obj;
	while (obj)
	{
		obj->center = vec3_add(obj->center, translate);
		obj = obj->next;
	}
	vp->scene->cam.pos = translate;
	vp->scene->light.pos = vec3_add(vp->scene->light.pos, translate);
}

static void	rotate_scene(t_quat q, t_viewport *vp)
{
	t_obj	*obj;

	obj = vp->scene->obj;
	while (obj)
	{
		obj->center = rotate(obj->center, q);
		if (obj->type != SPHERE)
			obj->dir = normalize(rotate(obj->dir, q));
		obj = obj->next;
	}
	vp->scene->light.pos = rotate(vp->scene->light.pos, q);
	vp->scene->cam.dir = normalize(rotate(vp->scene->cam.dir, q));
}

static void	start_panning(int keycode, t_viewport *vp)
{
	t_quat	q;
	t_vec3	rot_center;
	t_vec3	rot_axis;
	int		angle;

	rot_axis = get_rotation_axis(keycode, vp, &angle);
	if (vp->selected)
		rot_center = vp->selected->center;
	else
		rot_center = vp->scene->cam.pos;
	origin_translation(vp, rot_center, to_origin);
	q = get_quaternion(get_radian(angle), rot_axis);
	if (vp->selected)
		vp->selected->dir = normalize(rotate(vp->selected->dir, q));
	else
		rotate_scene(q, vp);
	origin_translation(vp, rot_center, revert);
}

void	panning(int key, t_viewport *vp)
{
	if (vp->selected && vp->selected->type == SPHERE)
	{
		printf("\nSphere cannot be rotated !!\n");
		printf("Please choose CYLINDER or PLANE for rotation.\n\n");
		return ;
	}
	else
		start_panning(key, vp);
	transformation_info(vp->selected, vp->scene->cam);
}
