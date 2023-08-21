/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_uv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 00:05:27 by suchua            #+#    #+#             */
/*   Updated: 2023/08/21 16:40:53 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//	2 * MPI return angle between -0.5 -> 1.0
//	+0.5 shift range to 0.0 -> 1.0
void	texture_sphere_uv(t_tuv *g)
{
	g->u = atan2(g->ci.x, g->ci.z) / (2 * M_PI) + 0.5;
	g->v = g->ci.y * 0.5 + 0.5;
	g->u *= (g->t_width);
	g->v *= (g->t_height);
	g->u = nb_clamp(g->u, 0.0, g->t_width - 1);
	g->v = nb_clamp(g->v, 0.0, g->t_height - 1);
}

void	texture_plane_uv(t_tuv *g)
{
	double	u;
	double	v;

	u = g->ci.x;
	v = g->ci.z;
	u *= (g->t_width - 1);
	v *= (g->t_height - 1);
	g->u = nb_clamp(fabs(u), 0.0, g->t_width - 1);
	g->v = nb_clamp(fabs(v), 0.0, g->t_height - 1);
}

void	texture_cy_uv(t_tuv *g)
{
	double	theta;
	double	y;
	double	u;
	double	v;

	theta = atan2(g->ci.z, g->ci.x);
	y = g->ci.y;
	u = theta / (2 * M_PI);
	v = y / g->h;
	u -= floor(u);
	u *= (g->t_width - 1);
	v *= (g->t_height - 1);
	g->u = nb_clamp(fabs(u), 0.0, g->t_width - 1);
	g->v = nb_clamp(fabs(v), 0.0, g->t_height - 1);
}

void	texture_cone_uv(t_tuv *g)
{
	double	theta;
	double	h;
	double	u;
	double	v;

	theta = atan2(g->ci.z, g->ci.x);
	h = g->ci.y;
	u = theta / (2 * M_PI);
	v = h / g->h;
	u -= floor(u);
	u *= (g->t_width - 1);
	v *= (g->t_height - 1);
	g->u = nb_clamp(fabs(u), 0.0, g->t_width - 1);
	g->v = nb_clamp(fabs(v), 0.0, g->t_height - 1);
}
