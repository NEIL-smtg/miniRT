/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:47:09 by mmuhamad          #+#    #+#             */
/*   Updated: 2023/07/21 03:22:31 by suchua           ###   ########.fr       */
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
	t_mat4	rotation;
	t_mat4	view_rot;

	rotation = get_x_rotation_mat(get_radian(5));
	view_rot = mat44_mul_mat44(vp->view_mat, rotation);
	// vp->scene->cam.pos = convert_to_view_space(view_rot, vp->scene->cam.pos);
	vp->scene->cam.dir = convert_to_view_space(view_rot, vp->scene->cam.dir);
	vp->scene->cam.dir = normalize(vp->scene->cam.dir);
	vp->view_mat = get_view_matrix(vp->scene->cam);
	vp->inv_view_mat = inverse_mat4(vp->view_mat);
	// print_mat4(vp->inv_view_mat);
	world_to_camera(view_rot, vp->scene);
	printf("e clicked\n");
	// print_scene(vp->scene);
	render(vp, *vp->scene);
}

void	ft_panning_left(t_viewport *vp)
{
	t_mat4	rotation;
	t_mat4	view_rot;

	rotation = get_x_rotation_mat(get_radian(-5));
	view_rot = mat44_mul_mat44(vp->view_mat, rotation);
	// vp->scene->cam.pos = convert_to_view_space(view_rot, vp->scene->cam.pos);
	vp->scene->cam.dir = convert_to_view_space(view_rot, vp->scene->cam.dir);
	vp->scene->cam.dir = normalize(vp->scene->cam.dir);
	vp->view_mat = get_view_matrix(vp->scene->cam);
	vp->inv_view_mat = inverse_mat4(vp->view_mat);
	rotation_transformation(view_rot, vp->scene);
	printf("q clicked\n");
	render(vp, *vp->scene);
}

