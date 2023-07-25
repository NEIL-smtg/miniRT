/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:21:38 by suchua            #+#    #+#             */
/*   Updated: 2023/07/25 23:46:16 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transformation.h"
#include "keys.h"

static void	x_translation(enum e_movement dir, t_viewport *vp)
{
	if (dir == left)
		vp->scene->cam.pos.x -= 0.1f;
	else
		vp->scene->cam.pos.x += 0.1f;
}

static void	y_translation(enum e_movement dir, t_viewport *vp)
{
	if (dir == down)
		vp->scene->cam.pos.y += 0.1f;
	else
		vp->scene->cam.pos.y -= 0.1f;
}

static void	z_translation(enum e_movement dir, t_viewport *vp)
{
	t_vec3	pos;
	t_vec3	n;

	pos = vp->scene->cam.pos;
	n = vp->scene->cam.dir;
	if (dir == backward)
		n = vec3_mul(-1.0, n);
	vp->scene->cam.pos = vec3_add(pos, vec3_mul(0.5, n));		
}

void	translation(int keycode, t_viewport *vp)
{
	if (keycode == KEY_D)
		x_translation(right, vp);
	else if (keycode == KEY_A)
		x_translation(left, vp);
	else if (keycode == KEY_W)
		z_translation(forward, vp);
	else if (keycode == KEY_S)
		z_translation(backward, vp);
	else if (keycode == KEY_UP)
		y_translation(up, vp);
	else
		y_translation(down, vp);
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
