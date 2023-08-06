/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:21:38 by suchua            #+#    #+#             */
/*   Updated: 2023/08/06 17:14:17 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transformation.h"
#include "keys.h"
#include <stdio.h>

static void	x_translation(int key, t_vec3 *pos)
{
	if (key == KEY_A)
		pos->x -= MOVEMENT;
	else
		pos->x += MOVEMENT;
}

static void	y_translation(int key, t_vec3 *pos)
{
	if (key == KEY_UP)
		pos->y += MOVEMENT;
	else
		pos->y -= MOVEMENT;
}

static void	z_translation(int key, t_vec3 *pos)
{
	if (key == KEY_W)
		pos->z -= MOVEMENT;
	else
		pos->z += MOVEMENT;
}

void	translation(int keycode, t_viewport *vp)
{
	t_vec3	*pos;

	pos = &vp->scene->cam.pos;
	if (vp->selected)
		pos = &vp->selected->center;
	if (keycode == KEY_D || keycode == KEY_A)
		x_translation(keycode, pos);
	else if (keycode == KEY_UP || keycode == KEY_DOWN)
		y_translation(keycode, pos);
	else if (keycode == KEY_S || keycode == KEY_W)
		z_translation(keycode, pos);
	else
		return ;
	transformation_info(vp->selected, vp->scene->cam);
}

bool	is_translation_key(int keycode)
{
	if (keycode == KEY_D || keycode == KEY_A)
		return (true);
	if (keycode == KEY_W || keycode == KEY_S)
		return (true);
	if (keycode == KEY_UP || keycode == KEY_DOWN)
		return (true);
	return (false);
}
