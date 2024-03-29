/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:37:58 by suchua            #+#    #+#             */
/*   Updated: 2023/08/16 16:56:42 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	angle_handler(int keycode, t_obj *selected)
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

static t_vec3	get_rotation_axis(int keycode, t_viewport *vp, int *angle)
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

static void	origin_translation(t_viewport *vp, t_vec3 rot_center, \
	enum e_rotation rot)
{
	t_vec3	translate;
	t_obj	*obj;
	t_light	*lg;

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
	lg = vp->scene->light;
	while (lg)
	{
		lg->pos = vec3_add(lg->pos, translate);
		lg = lg->next;
	}
}

static void	rotate_scene(t_quat q, t_viewport *vp)
{
	t_obj	*obj;
	t_light	*lg;

	obj = vp->scene->obj;
	while (obj)
	{
		obj->center = rotate(obj->center, q);
		if (obj->type != SPHERE)
			obj->dir = normalize(rotate(obj->dir, q));
		obj = obj->next;
	}
	lg = vp->scene->light;
	while (lg)
	{
		lg->pos = rotate(lg->pos, q);
		lg = lg->next;
	}
	vp->scene->cam.dir = normalize(rotate(vp->scene->cam.dir, q));
}

void	start_panning(int keycode, t_viewport *vp)
{
	t_quat	q;
	t_vec3	rot_center;
	t_vec3	rot_axis;
	int		angle;

	if (vp->selected)
		rot_center = vp->selected->center;
	else
		rot_center = vp->scene->cam.pos;
	origin_translation(vp, rot_center, to_origin);
	rot_axis = get_rotation_axis(keycode, vp, &angle);
	q = get_quaternion(get_radian(angle), rot_axis);
	if (vp->selected)
		vp->selected->dir = normalize(rotate(vp->selected->dir, q));
	else
		rotate_scene(q, vp);
	origin_translation(vp, rot_center, revert);
}
