/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 22:57:43 by suchua            #+#    #+#             */
/*   Updated: 2023/08/22 16:43:59 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_viewport(t_viewport *vp, t_camera cam)
{
	vp->aspect_ratio = 16.0 / 9.0;
	vp->h = HEIGHT;
	vp->w = HEIGHT * vp->aspect_ratio;
	vp->focal = tan(cam.fov / 2);
	vp->view_mat = get_view_matrix(cam);
	vp->inv_view_mat = inverse_mat4(vp->view_mat);
}

void	create_mlx(t_viewport *vp, t_scene *scene)
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
	vp->scene = scene;
	vp->selected = NULL;
	vp->edit = false;
	vp->checkerboard = false;
}

int	main(int ac, char **av)
{
	t_scene		scene;
	t_viewport	vp;

	if (!valid_arg(ac, av))
		exit (1);
	if (!get_input(av[1], &scene))
		exit (1);
	init_viewport(&vp, scene.cam);
	world_to_camera(vp.inv_view_mat, &scene);
	create_mlx(&vp, &scene);
	init_texture(av[2], &vp.texture, vp.mlx);
	print_scene(&scene);
	render(&vp);
	hooks(&vp);
	exit (0);
}
