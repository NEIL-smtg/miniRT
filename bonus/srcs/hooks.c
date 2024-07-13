/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:07:37 by suchua            #+#    #+#             */
/*   Updated: 2024/07/13 21:21:50 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//	closing window
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
	render(vp);
	return (0);
}

//	simply reset to setting of object to default
static void	reset_selected_object(t_obj **selected, t_obj *found)
{
	*selected = found;
	if (!found)
		return ;
	(*selected)->edit_d = false;
	(*selected)->edit_h = false;
	(*selected)->tmp_color = get_selected_color((*selected)->rgb);
}

//	return true only if these 3 buttons on mouse are pressed
static bool	validGesture(bool edit, int button)
{
	if (!edit)
		return (false);
	if (button == MOUSE_BUTTON_LEFT)
		return (true);
	if (button == MOUSE_SCROLL_DOWN || button == MOUSE_SCROLL_UP)
		return (true);
	return (false);
}

//	shoot the ray using x,y of mouse
static void	select_obj_handler(int x, int y, t_viewport *vp)
{
	int		pixel[2];
	t_ray	ray;
	t_obj	*select;

	select = NULL;
	pixel[0] = x;
	pixel[1] = y;
	ray.origin = vp->scene->cam.pos;
	ray.dir = get_ray_dir(pixel, vp);
	get_closest_obj(ray, vp->scene->obj, &select, vp->edit);
	if (select != vp->selected)
	{
		reset_selected_object(&vp->selected, select);
		selected_msg(vp->selected);
	}
	else
		printf("\nYou are editing the same object.\n");
}

//	scrolling simply moving object in z-direction
static int	mouse_event(int button, int x, int y, t_viewport *vp)
{
	if (!validGesture(vp->edit, button))
		return (0);
	if (button == MOUSE_BUTTON_LEFT)
		select_obj_handler(x, y, vp);
	else if (button == MOUSE_SCROLL_UP)
		translation(KEY_W, vp);
	else
		translation(KEY_S, vp);
	render(vp);
	return (0);
}

//	hooks handler
void	hooks(t_viewport *vp)
{
	mlx_hook(vp->win, KEY_PRESS, (1L << 0), key_pressed, vp);
	mlx_hook(vp->win, CLOSE_WINDOW, (1L << 0), ft_close, vp);
	mlx_mouse_hook(vp->win, mouse_event, vp);
	mlx_loop(vp->mlx);
}
