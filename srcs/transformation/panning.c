/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:37:58 by suchua            #+#    #+#             */
/*   Updated: 2023/08/21 12:20:54 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
