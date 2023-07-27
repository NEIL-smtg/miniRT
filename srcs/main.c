/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid Date        by              +#+  #+#    #+#             */
/*   Updated: 2023/07/27 16:01:53 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_viewport(t_viewport *vp, t_camera cam)
{
	vp->aspect_ratio = 16.0 / 9.0;
	vp->h = HEIGHT;
	vp->w = HEIGHT * vp->aspect_ratio;
	// vp->origin = cam.pos;
	// vp->focal = get_focal_length(cam.fov, vp->w);
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
}

int	ft_close(t_viewport *vp)
{
	mlx_destroy_window(vp->mlx, vp->win);
	exit (0);
}

int	movement(int keycode, t_viewport *vp)
{
	// printf("%d\n", keycode);
	if (keycode == KEY_ESC)
		ft_close(vp);
	if (keycode == KEY_SHIFT)
		ft_edit(vp);
	// rotate obj using 7,8,9,0(can only only rotate when have selected only)
	if (keycode == KEY_SEVEN || keycode == KEY_EIGHT
		|| keycode == KEY_NINE || keycode == KEY_ZERO)
		ft_obj_panning(keycode, vp);
	if (!vp->edit)
		return (0);
	else if (keycode == KEY_R)
	{
		render(vp, *vp->scene);
	}
	if (is_translation_key(keycode))
		translation(keycode, vp);
	else if (keycode >= KEY_ONE && keycode <= KEY_FIVE)
		ft_cam_panning(keycode, vp);
	else if (vp->selected)
		edit_property(keycode, vp->selected);
	else
		return (0);
	render_edit(vp, *vp->scene);
	return (0);
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
	mlx_hook(vp.win, 2, (1L << 0), movement, &vp);
	mlx_hook(vp.win, 17, (1L << 0), ft_close, &vp);
	mlx_loop(vp.mlx);
	return (0);
}
