/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:47:09 by mmuhamad          #+#    #+#             */
/*   Updated: 2023/07/25 16:02:56 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_forward(t_viewport *vp)
{
	t_vec3	pos;
	t_vec3	dir;

	pos = vp->scene->cam.pos;
	dir = vp->scene->cam.dir;
	vp->scene->cam.pos = vec3_add(pos, vec3_mul(0.5, dir));
	render(vp, *vp->scene);
}

void	ft_backward(t_viewport *vp)
{
	t_vec3	pos;
	t_vec3	dir;

	pos = vp->scene->cam.pos;
	dir = vp->scene->cam.dir;
	vp->scene->cam.pos = vec3_sub(pos, vec3_mul(0.5, dir));
	render(vp, *vp->scene);
}

void	ft_right(t_viewport *vp)
{
	vp->scene->cam.pos.x += 0.1f;
	render(vp, *vp->scene);
}

void	ft_left(t_viewport *vp)
{
	vp->scene->cam.pos.x -= 0.1f;
	render(vp, *vp->scene);
}

void	ft_up(t_viewport *vp)
{
	vp->scene->cam.pos.y += 0.1f;
	render(vp, *vp->scene);
}

void	ft_down(t_viewport *vp)
{
	vp->scene->cam.pos.y -= 0.1f;
	render(vp, *vp->scene);
}

/*
	x rotation returns up
	y rotation returns forward
	z rotation returns right
*/
t_vec3	get_rotation_axis(int keycode, t_mat4 view_mat, int *angle)
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

void	ft_cam_panning(int keycode, t_viewport *vp)
{
	t_quat	q;
	t_vec3	rot_center;
	t_vec3	rot_axis;
	int		angle;

	// if (vp->edit == false)
	// 	return ;
	rot_axis = get_rotation_axis(keycode, vp->view_mat, &angle);
	rot_center = vp->scene->cam.pos;
	origin_translation(vp->scene, rot_center, to_origin);
	q = get_quaternion(get_radian(angle), rot_axis);
	quaternion_rotation(q, vp);
	origin_translation(vp->scene, rot_center, revert);
	// print_scene(vp->scene);
	render(vp, *vp->scene);
}
