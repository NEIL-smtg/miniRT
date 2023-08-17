/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_uv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 00:05:27 by suchua            #+#    #+#             */
/*   Updated: 2023/08/08 01:10:29 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	texture_sphere_uv(t_tuv *g)
{
	double	theta;
	double	phi;
	double	uu;
	double	vv;

	theta = atan2(g->ci.z, g->ci.x);
	phi = acos(g->ci.y / g->r);
	uu = theta / (2 * M_PI);
	vv = phi / M_PI;
	uu -= floor(uu);
	uu = uu * (g->t_height - 1);
	vv = vv * (g->t_width - 1);
	g->u = nb_clamp(fabs(uu), 0, g->t_width - 1);
	g->v = nb_clamp(fabs(vv), 0, g->t_height - 1);
}

void	texture_plane_uv(t_tuv *g)
{
	double	u;
	double	v;

	u = g->ci.x;
	v = g->ci.z;
	u *= (g->t_width - 1);
	v *= (g->t_height - 1);
	g->u = nb_clamp(fabs(u), 0, g->t_width - 1);
	g->v = nb_clamp(fabs(v), 0, g->t_height - 1);
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
	g->u = nb_clamp(fabs(u), 0, g->t_width - 1);
	g->v = nb_clamp(fabs(v), 0, g->t_height - 1);
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
	g->u = nb_clamp(fabs(u), 0, g->t_width - 1);
	g->v = nb_clamp(fabs(v), 0, g->t_height - 1);
}
