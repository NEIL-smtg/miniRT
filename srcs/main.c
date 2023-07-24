/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 00:44:15 by suchua            #+#    #+#             */
/*   Updated: 2023/07/24 18:37:43 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "keys.h"

void	init_viewport(t_viewport *vp, t_camera cam)
{
	vp->aspect_ratio = 16.0 / 9.0;
	vp->h = HEIGHT;
	vp->w = HEIGHT * vp->aspect_ratio;
	vp->origin = cam.pos;
	vp->focal = get_focal_length(cam.fov, vp->w);
	vp->focal = tan(cam.fov / 2);
	
	double halfWidth = vp->aspect_ratio * vp->focal;

	// Calculate the center point of the near plane
	t_vec3 center = vec3_add(cam.pos, cam.dir);

	// Calculate the corner points of the near plane
	vp->p0 = vec3_add(center, new_vec3(-halfWidth, vp->focal, 0));
	vp->p1 = vec3_add(center, new_vec3(halfWidth, vp->focal, 0));
	vp->p2 = vec3_add(center, new_vec3(-halfWidth, -vp->focal, 0));

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
	vp->edit = false;
}

void	movement(int keycode, t_viewport *vp)
{
	if (vp->edit == false)
		return ;
	clean_img(vp);
	if (keycode == KEY_D)
		ft_right(vp);
	else if (keycode == KEY_A)
		ft_left(vp);
	else if (keycode == KEY_W)
		ft_forward(vp);
	else if (keycode == KEY_S)
		ft_backward(vp);
	else if (keycode == KEY_UP)
		ft_up(vp);
	else if (keycode == KEY_DOWN)
		ft_down(vp);
	else if (keycode == KEY_Q)
		ft_panning_left(vp);
	else if (keycode == KEY_E)
		ft_panning_right(vp);
	else
		return ;
	render_edit(vp, *vp->scene);
}

int	key_hook(int keycode, t_viewport *vp)
{
	// printf("%d\n", keycode);
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(vp->mlx, vp->win);
		exit(1);
	}
	else if (keycode == KEY_SHIFT)
		ft_edit(vp);
	else if (keycode == KEY_R && vp->edit == true)
		render(vp, *vp->scene);
	else
		movement(keycode, vp);
	return (0);
}

int	ft_close(t_viewport *vp)
{
	mlx_destroy_window(vp->mlx, vp->win);
	exit (0);
}

int	main(int ac, char **av)
{
	t_scene		scene;
	t_viewport	vp;

	if (!valid_arg(ac, av))
		return (1);
	if (!get_input(av[1], &scene))
		return (1);
	// print_scene(&scene);
	init_viewport(&vp, scene.cam);
	world_to_camera(vp.inv_view_mat, &scene);
	print_scene(&scene);
	create_mlx(&vp, &scene);
	render(&vp, scene);
	mlx_hook(vp.win, 2, (1L << 0), key_hook, &vp);
	mlx_hook(vp.win, 17, (1L << 0), ft_close, &vp);
	mlx_loop(vp.mlx);
	return (0);
}
