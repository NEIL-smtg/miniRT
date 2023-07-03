/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 00:44:15 by suchua            #+#    #+#             */
/*   Updated: 2023/07/02 01:28:42 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mat3	get_transform_matrix(t_camera cam)
{
	t_vec3	right;
	t_vec3	up;
	t_vec3	forward;

	forward = normalize(cam.dir);
	up = new_vec3(0, 1, 0);
	if (forward.z == 1.0)
		right = new_vec3(1, 0, 0);
	else if (forward.z == -1.0)
		right = new_vec3(-1, 0, 0);
	else
	{
		right = normalize(new_vec3(forward.y, -forward.x, 0));
		up = vec3_cross(right, forward);
	}
	return (new_mat3(
			right,
			up,
			forward
		));
}

void	init_viewport(t_viewport *vp, t_camera cam)
{
	vp->aspect_ratio = 16.0 / 9.0;
	vp->h = HEIGHT;
	vp->w = HEIGHT * vp->aspect_ratio;
	vp->origin = cam.pos;
	vp->focal = get_focal_length(cam.fov, vp->w);
	vp->transform_mat = get_transform_matrix(cam);
}

t_vec3	convert_to_cam(t_mat3 transform_mat, t_vec3 v)
{
	t_vec3	res;

	res.x = vec3_dot(transform_mat.r1, v);
	res.y = vec3_dot(transform_mat.r2, v);
	res.z = vec3_dot(transform_mat.r3, v);
	return (res);
}

void	world_to_camera(t_mat3 transform_mat, t_scene *sc)
{
	t_obj	*tmp;

	sc->cam.pos = convert_to_cam(transform_mat, sc->cam.pos);
	sc->cam.dir = convert_to_cam(transform_mat, sc->cam.dir);
	sc->light.pos = convert_to_cam(transform_mat, sc->light.pos);
	tmp = sc->obj;
	while (tmp)
	{
		tmp->center = convert_to_cam(transform_mat, tmp->center);
		if (tmp->type != SPHERE)
			tmp->dir = convert_to_cam(transform_mat, tmp->dir);
		tmp = tmp->next;
	}
}

void	create_mlx(t_viewport *vp)
{
	vp->mlx = mlx_init();
	vp->win = mlx_new_window(vp->mlx, (int) vp->w, (int) vp->h, TITLE);
	vp->img.ptr = mlx_new_image(vp->mlx, (int) vp->w, (int) vp->h);
	vp->img.data_addr = mlx_get_data_addr(
			vp->img.ptr,
			&vp->img.bpp,
			&vp->img.line_size,
			&vp->img.endian
			);
}

int	main(int ac, char **av)
{
	t_scene		scene;
	t_viewport	vp;

	if (!valid_arg(ac, av))
		return (1);
	get_input(av[1], &scene);
	init_viewport(&vp, scene.cam);
	world_to_camera(vp.transform_mat, &scene);
	create_mlx(&vp);
	print_scene(&scene);
	render(&vp, scene);
	mlx_loop(vp.mlx);
	return (0);
}
