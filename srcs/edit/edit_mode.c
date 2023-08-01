/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:30:19 by mmuhamad          #+#    #+#             */
/*   Updated: 2023/08/01 13:29:44 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	close_edit(t_viewport *vp)
{
	vp->edit = false;
	if (vp->checkerboard == false)
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
	else if (keycode == KEY_B)
		vp->checkerboard = true;
	else if (vp->selected)
		edit_property(keycode, vp->selected);
	else
		return (false);
	return (true);
}
