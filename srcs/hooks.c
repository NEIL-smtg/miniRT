/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:07:37 by suchua            #+#    #+#             */
/*   Updated: 2023/07/28 23:50:08 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	ft_close(t_viewport *vp)
{
	mlx_destroy_window(vp->mlx, vp->win);
	exit (0);
}

static int	close_edit(t_viewport *vp)
{
	vp->edit = false;
	vp->selected = NULL;
	clean_img(vp);
	render(vp, *vp->scene);
	return (0);
}

static int	key_pressed(int keycode, t_viewport *vp)
{
	if (keycode == KEY_ESC)
		ft_close(vp);
	if (keycode == KEY_SHIFT)
		ft_edit(vp);
	if (!vp->edit)
		return (0);
	if (keycode == KEY_R)
		return (close_edit(vp));
	else if (is_translation_key(keycode))
		translation(keycode, vp);
	else if (keycode >= KEY_ONE && keycode <= KEY_FIVE)
		panning(keycode, vp);
	else if (keycode == KEY_C)
		vp->selected = NULL;
	else if (vp->selected)
		edit_property(keycode, vp->selected);
	else
		return (0);
	render(vp, *vp->scene);
	return (0);
}

static int	mouse_event(int button, int x, int y, t_viewport *vp)
{
	int		pixel[2];
	t_ray	ray;

	// printf("Mouse clicked\n");
	if (!vp->edit)
		return (0);
	pixel[0] = x;
	pixel[1] = y;
	vp->selected = NULL;
	ray.origin = vp->scene->cam.pos;
	ray.dir = get_ray_dir(pixel, vp, ray.origin);
	get_closest_obj(ray, vp->scene->obj, &vp->selected);
	if (!vp->selected)
	{
		render(vp, *vp->scene);
		return (0);
	}
	vp->selected->edit_d = false;
	vp->selected->edit_h = false;
	vp->selected->tmp_color = get_selected_color(vp->selected->rgb);
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
