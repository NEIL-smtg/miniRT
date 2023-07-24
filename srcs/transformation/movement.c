/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:47:09 by mmuhamad          #+#    #+#             */
/*   Updated: 2023/07/24 02:46:10 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_forward(t_viewport *vp)
{
	vp->scene->cam.pos.z -= 1.0f;
	render(vp, *vp->scene);
}

void	ft_backward(t_viewport *vp)
{
	vp->scene->cam.pos.z += 1.0f;
	render(vp, *vp->scene);
}

void	ft_right(t_viewport *vp)
{
	vp->scene->cam.pos.x += 1.0f;
	render(vp, *vp->scene);
}

void	ft_left(t_viewport *vp)
{
	vp->scene->cam.pos.x -= 1.0f;
	render(vp, *vp->scene);
}

void	ft_up(t_viewport *vp)
{
	vp->scene->cam.pos.y += 1.0f;
	render(vp, *vp->scene);
}

void	ft_down(t_viewport *vp)
{
	vp->scene->cam.pos.y -= 1.0f;
	render(vp, *vp->scene);
}

void	ft_panning_right(t_viewport *vp)
{
	t_quat	q;

	printf("e clicked\n");
	q = get_quaternion(get_radian(10), get_cam_up(vp->view_mat));
	// vp->scene->cam.pos = rotate(vp->scene->cam.pos, q);
	vp->scene->cam.dir = normalize(rotate(vp->scene->cam.dir, q));
	vp->view_mat = get_view_matrix(vp->scene->cam);
	vp->inv_view_mat = inverse_mat4(vp->view_mat);
	rotation_transformation(vp->inv_view_mat, vp->scene);
	// print_scene(vp->scene);
	render(vp, *vp->scene);
}

void	ft_panning_left(t_viewport *vp)
{
	t_quat	q;

	printf("q clicked\n");
	q = get_quaternion(get_radian(-10), get_cam_up(vp->view_mat));
	vp->scene->cam.pos = rotate(vp->scene->cam.pos, q);
	vp->scene->cam.dir = normalize(rotate(vp->scene->cam.dir, q));
	vp->view_mat = get_view_matrix(vp->scene->cam);
	vp->inv_view_mat = inverse_mat4(vp->view_mat);
	world_to_camera(vp->inv_view_mat, vp->scene);
	// print_scene(vp->scene);
	render(vp, *vp->scene);
}

