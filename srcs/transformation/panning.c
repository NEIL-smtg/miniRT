/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:37:58 by suchua            #+#    #+#             */
/*   Updated: 2023/07/29 22:30:19 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	get_obj_up(t_vec3 forward)
{
	t_vec3	right;
	t_vec3	up;

	if (fabs(forward.y) >= 0.99)
	{
		right = new_vec3(forward.y, -forward.x, forward.z);
	}
	else
		right = normalize(vec3_cross(forward, new_vec3(0, 1, 0)));
	up = vec3_cross(right, forward);
	return (normalize(up));
}

t_vec3	get_obj_right(t_vec3 forward)
{
	t_vec3	up;
	t_vec3	right;

	if (fabs(forward.y) >= 0.99)
	{
		right = new_vec3(forward.y, -forward.x, forward.z);
	}
	else
	{
		right = normalize(vec3_cross(forward, new_vec3(0, 1, 0)));
	}
	// up = normalize(vec3_cross(right, forward));
	return (right);
}

t_vec3	get_obj_forward(t_vec3 forward)
{
	return (forward);
}

static t_vec3	get_up_vec(t_viewport *vp)
{
	printf("\nROTATING in X-AXIS\n");
	if (vp->selected)
		return (get_obj_up(vp->selected->dir));
	else
		return (get_cam_up(vp->view_mat));
}

static t_vec3	get_right_vec(t_viewport *vp)
{
	printf("\nROTATING in Y-AXIS\n");
	if (vp->selected)
		return (get_obj_right(vp->selected->dir));
	else
		return (get_cam_right(vp->view_mat));
}

static t_vec3	get_forward_vec(t_viewport *vp)
{
	printf("\nROTATING in Z-AXIS\n");
	if (vp->selected)
		return (get_obj_forward(vp->selected->dir));
	else
		return (get_cam_forward(vp->view_mat));
}

static t_vec3	get_rotation_axis(int keycode, t_viewport *vp, int *angle)
{
	if (keycode % 2 == 0)
		*angle = -ANGLE_ROTATION;
	else
		*angle = ANGLE_ROTATION;
	if (keycode == KEY_ONE || keycode == KEY_TWO)
		return (get_up_vec(vp));
	else if (keycode == KEY_THREE || keycode == KEY_FOUR)
		return (get_right_vec(vp));
	else
		return (get_forward_vec(vp));
}

static void	origin_translation(t_viewport *vp, t_vec3 rot_center,\
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

void	transformation_info(t_obj *selected, t_camera cam)
{
	printf("\nAfter transformation :\n");
	if (selected)
	{
		if (selected->type == SPHERE)
			printf("SPHERE\n");
		else if (selected->type == PLANE)
			printf("PLANE\n");
		else
			printf("CYLINDER\n");
		print_vec3(selected->center, "POSITION");
		if (selected->type != SPHERE)
			print_vec3(selected->dir, "NORMAL");
		return ;
	}
	printf("CAMERA\n");
	print_vec3(cam.pos, "POSITION");
	print_vec3(cam.dir, "NORMAL");
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
