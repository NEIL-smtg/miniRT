/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:21:38 by suchua            #+#    #+#             */
/*   Updated: 2023/07/27 15:52:15 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transformation.h"
#include "keys.h"
#include <stdio.h>

static void	x_translation(enum e_movement dir, t_vec3 *pos)
{
	if (dir == left)
		pos->x--;
	else
		pos->x++;
}

static void	y_translation(enum e_movement dir, t_vec3 *pos)
{
	if (dir == up)
		pos->y++;
	else
		pos->y--;
}

static void	z_translation(enum e_movement dir, t_vec3 *pos, t_vec3 normal)
{
	if (dir == forward)
		*pos = vec3_add(*pos, vec3_mul(0.5, normal));
	else
		*pos = vec3_add(*pos, vec3_mul(-0.5, normal));
}

void	translation(int keycode, t_viewport *vp)
{
	t_vec3	*pos;
	t_vec3	dir;

	pos = &vp->scene->cam.pos;
	dir = vp->scene->cam.dir;
	if (vp->selected)
	{
		pos = &vp->selected->center;
		dir = vp->selected->dir;
	}
	if (keycode == KEY_D)
		x_translation(right, pos);
	else if (keycode == KEY_A)
		x_translation(left, pos);
	else if (keycode == KEY_UP)
		y_translation(up, pos);
	else if (keycode == KEY_DOWN)
		y_translation(down, pos);
	else if (vp->selected && vp->selected->type == SPHERE && keycode == KEY_S)
		(vp->selected->center.z)++;
	else if (vp->selected && vp->selected->type == SPHERE && keycode == KEY_W)
		(vp->selected->center.z)--;
	else if (keycode == KEY_S)
		z_translation(backward, pos, dir);
	else if (keycode == KEY_W)
		z_translation(forward, pos, dir);
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
