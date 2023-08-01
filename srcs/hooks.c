/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:07:37 by suchua            #+#    #+#             */
/*   Updated: 2023/08/02 00:39:28 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	ft_close(t_viewport *vp)
{
	mlx_destroy_window(vp->mlx, vp->win);
	exit (0);
}

static int	key_pressed(int keycode, t_viewport *vp)
{
	if (keycode == KEY_ESC)
		ft_close(vp);
	if (keycode == KEY_SHIFT)
		ft_edit(vp);
	if (!vp->edit)
		return (0);
	if (!is_edit_key(keycode, vp))
		return (0);
	render(vp, *vp->scene);
	return (0);
}

static void	reset_selected_object(t_obj **selected, t_obj *found)
{
	*selected = found;
	if (!found)
		return ;
	(*selected)->edit_d = false;
	(*selected)->edit_h = false;
	(*selected)->tmp_color = get_selected_color((*selected)->rgb);
}

static int	mouse_event(int button, int x, int y, t_viewport *vp)
{
	int		pixel[2];
	t_ray	ray;
	t_obj	*select;

	if (!vp->edit)
		return (0);
	select = NULL;
	pixel[0] = x;
	pixel[1] = y;
	ray.origin = vp->scene->cam.pos;
	ray.dir = get_ray_dir(pixel, vp, ray.origin);
	get_closest_obj(ray, vp->scene->obj, &select);
	if (select != vp->selected)
	{
		reset_selected_object(&vp->selected, select);
		selected_msg(vp->selected);
	}
	else
		printf("\nYou are editing the same object.\n");
	render(vp, *vp->scene);
	return (0);
}

void	hooks(t_viewport *vp)
{
	mlx_hook(vp->win, KEY_PRESS, (1L << 0), key_pressed, vp);
	mlx_hook(vp->win, CLOSE_WINDOW, (1L << 0), ft_close, vp);
	mlx_mouse_hook(vp->win, mouse_event, vp);
	mlx_loop(vp->mlx);
}
