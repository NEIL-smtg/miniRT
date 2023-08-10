/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:30:19 by mmuhamad          #+#    #+#             */
/*   Updated: 2023/08/10 19:48:14 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	close_edit(t_viewport *vp)
{
	vp->edit = false;
	vp->selected = NULL;
	clean_img(vp);
	render(vp, *vp->scene);
	return (0);
}

static void	camera_mode(t_obj **selected)
{
	if (!*selected)
		return ;
	*selected = NULL;
	selected_msg(*selected);
}

static void	checkerboard_mode(t_obj **selected)
{
	(*selected)->checkerboard = !(*selected)->checkerboard;
	if ((*selected)->checkerboard)
		printf("\nCheckerboard texture applied.\n");
	else
		printf("\nCheckerboard texture unapplied.\n");
}

static void	bump_mode(t_obj **selected)
{
	(*selected)->bump = !(*selected)->bump;
	if ((*selected)->bump)
		printf("\nBump texture applied.\n");
	else
		printf("\nBump texture unapplied.\n");
}

//	key 5 = 23, key 6 = 22
bool	is_edit_key(int keycode, t_viewport *vp)
{
	if (keycode == KEY_R)
		return (close_edit(vp));
	else if (is_translation_key(keycode))
		translation(keycode, vp);
	else if (keycode >= KEY_ONE && keycode <= KEY_FIVE)
		panning(keycode, vp);
	else if (keycode == KEY_C)
		camera_mode(&vp->selected);
	else if (vp->selected && keycode == KEY_B)
		checkerboard_mode(&vp->selected);
	else if (vp->selected && keycode == KEY_V && vp->texture.bump_map)
		bump_mode(&vp->selected);
	else if (vp->selected)
		edit_property(keycode, vp->selected);
	else
		return (false);
	return (true);
}
