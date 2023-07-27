/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_rotation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 01:43:56 by suchua            #+#    #+#             */
/*   Updated: 2023/07/27 15:54:43 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transformation.h"
#include "quaternion.h"
#include "keys.h"
#include "minirt.h"

static void	origin_translation(t_scene *sc, t_vec3 rot_center,
		enum e_rotation rot)
{
	t_vec3	translate;
	t_obj	*obj;

	translate = rot_center;
	if (rot == to_origin)
		translate = vec3_mul(-1, rot_center);
	obj = sc->obj;
	while (obj)
	{
		obj->center = vec3_add(obj->center, translate);
		obj = obj->next;
	}
	sc->cam.pos = vec3_add(sc->cam.pos, translate);
	sc->light.pos = vec3_add(sc->light.pos, translate);
}

/*
	x rotation returns up
	y rotation returns forward
	z rotation returns right
*/
static t_vec3	get_rotation_axis(int keycode, t_mat4 view_mat, int *angle)
{
	if (keycode % 2 == 0)
		*angle = -ANGLE_ROTATION;
	else
		*angle = ANGLE_ROTATION;
	if (keycode == KEY_ONE || keycode == KEY_TWO)
		return (get_cam_up(view_mat));
	else if (keycode == KEY_THREE || keycode == KEY_FOUR)
		return (get_cam_right(view_mat));
	else
		return (get_cam_forward(view_mat));
}

void	rotate_scene(t_quat q, t_viewport *vp)
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

void	ft_cam_panning(int keycode, t_viewport *vp)
{
	t_quat	q;
	t_vec3	rot_center;
	t_vec3	rot_axis;
	int		angle;

	rot_axis = get_rotation_axis(keycode, vp->view_mat, &angle);
	rot_center = vp->scene->cam.pos;
	origin_translation(vp->scene, rot_center, to_origin);
	q = get_quaternion(get_radian(angle), rot_axis);
	rotate_scene(q, vp);
	origin_translation(vp->scene, rot_center, revert);
	render_edit(vp, *vp->scene);
}
