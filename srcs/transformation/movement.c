/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:47:09 by mmuhamad          #+#    #+#             */
/*   Updated: 2023/07/20 19:51:01 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_forward(t_viewport *vp)
{
	size_t		size;

	vp->scene->cam.pos.z -= 1.0f;
	size = (size_t)((int) vp->h * vp->img.line_size
			+ (int) vp->w * (vp->img.bpp / 8));
	ft_memset(vp->img.data_addr, 0, size);
	render(vp, *vp->scene);
}

void	ft_backward(t_viewport *vp)
{
	size_t		size;

	vp->scene->cam.pos.z += 1.0f;
	size = (size_t)((int) vp->h * vp->img.line_size
			+ (int) vp->w * (vp->img.bpp / 8));
	ft_memset(vp->img.data_addr, 0, size);
	render(vp, *vp->scene);
}

void	ft_right(t_viewport *vp)
{
	size_t		size;

	vp->scene->cam.pos.x += 1.0f;
	size = (size_t)((int) vp->h * vp->img.line_size
			+ (int) vp->w * (vp->img.bpp / 8));
	ft_memset(vp->img.data_addr, 0, size);
	render(vp, *vp->scene);
}

void	ft_left(t_viewport *vp)
{
	size_t		size;

	vp->scene->cam.pos.x -= 1.0f;
	size = (size_t)((int) vp->h * vp->img.line_size
			+ (int) vp->w * (vp->img.bpp / 8));
	ft_memset(vp->img.data_addr, 0, size);
	render(vp, *vp->scene);
}

void	ft_up(t_viewport *vp)
{
	size_t		size;

	vp->scene->cam.pos.y += 1.0f;
	size = (size_t)((int) vp->h * vp->img.line_size
			+ (int) vp->w * (vp->img.bpp / 8));
	ft_memset(vp->img.data_addr, 0, size);
	render(vp, *vp->scene);
}

void	ft_down(t_viewport *vp)
{
	size_t		size;

	vp->scene->cam.pos.y -= 1.0f;
	size = (size_t)((int) vp->h * vp->img.line_size
			+ (int) vp->w * (vp->img.bpp / 8));
	ft_memset(vp->img.data_addr, 0, size);
	render(vp, *vp->scene);
}

void	ft_panning_right(t_viewport *vp)
{
	size_t		size;
	t_mat3		ret;
	t_mat3		rot_mat;
	t_mat3		theta_mat;

	theta_mat.r1 = new_vec3(1, 0, 0);
	theta_mat.r2 = new_vec3(0, cos(get_radian(3)), -sin(get_radian(3)));
	theta_mat.r3 = new_vec3(0, sin(get_radian(3)), cos(get_radian(3)));
	rot_mat = get_rotation_mat(vp->view_mat);
	vp->scene->cam.dir = mat33_mul_mat31(theta_mat, vp->scene->cam.dir);
	vp->view_mat = get_view_matrix(vp->scene->cam);
	vp->inv_view_mat = inverse_mat4(vp->view_mat);
	// rotation_transformation(vp->inv_view_mat, vp->scene);
	world_to_camera(vp->inv_view_mat, vp->scene);
	size = (size_t)((int) vp->h * vp->img.line_size
			+ (int) vp->w * (vp->img.bpp / 8));
	ft_memset(vp->img.data_addr, 0, size);
	render(vp, *vp->scene);
	print_scene(vp->scene);
}

void	ft_panning_left(t_viewport *vp)
{
	size_t		size;

	world_to_camera(vp->inv_view_mat, vp->scene);
	size = (size_t)((int) vp->h * vp->img.line_size
			+ (int) vp->w * (vp->img.bpp / 8));
	ft_memset(vp->img.data_addr, 0, size);
	render(vp, *vp->scene);
}

