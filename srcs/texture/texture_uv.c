/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_uv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 00:05:27 by suchua            #+#    #+#             */
/*   Updated: 2023/08/21 04:02:10 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	get_color_at(t_img texture, int y, int x)
{
	int				offset;
	unsigned char	*data;
	t_rgb			color;

	offset = y * texture.line_size + x * texture.bpp / 8;
	data = (unsigned char *) texture.data_addr;
	if (!data[offset])
		return (new_rgb(0, 0, 0));
	color.r = (double) data[offset + 2];
	color.g = (double) data[offset + 1];
	color.b = (double) data[offset];
	return (color);
}

t_rgb	filter_bilinear(t_tuv g)
{
	t_rgb	c[5];
	double	x0;
	double	y0;
	double	dx;
	double	dy;
	
	x0 = floor(g.u);
	y0 = floor(g.v);
	dx = g.u - x0;
	dy = g.v - y0;
	c[0] = get_color_at(g.texture, y0, x0);
	c[1] = get_color_at(g.texture, y0, x0 + 1);
	c[2] = get_color_at(g.texture, y0 + 1, x0);
	c[3] = get_color_at(g.texture, y0 + 1, x0 + 1);
	c[4] = rgb_scale((1 - dx) * (1 - dy), c[0]);
	c[4] = rgb_add(c[4], rgb_scale(dx * (1 - dy), c[1]));
	c[4] = rgb_add(c[4], rgb_scale((1 - dx) * dy, c[2]));
	c[4] = rgb_add(c[4], rgb_scale(dx * dy, c[3]));
	return (clamp(c[4], 0.0, 255.0));
}

//	2 * MPI return angle between -0.5 -> 1.0
//	+0.5 shift range to 0.0 -> 1.0
void	texture_sphere_uv(t_tuv *g)
{
	// g->u = atan2(g->ci.x, g->ci.z) / (2 * M_PI) + 0.5;
	// g->v = g->ci.y * 0.5 + 0.5;

	g->u = 0.5 + atan2(g->ci.z, g->ci.x) / (2 * M_PI);
	g->v = 0.5 + asin(g->ci.y) / M_PI;
	g->u *= (g->t_width);
	g->v *= (g->t_height);
	g->u = nb_clamp(g->u, 0.0, g->t_width - 1);
	g->v = nb_clamp(g->v, 0.0, g->t_height - 1);}

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
	g->u = atan2(g->ci.x, g->ci.z) / (2 * M_PI) + 0.5;
	g->v = (g->ci.y + g->h / 2) / g->h;
	g->u *= (g->t_width - 1);
	g->v *= (g->t_height - 1);
	// double	theta;
	// double	y;
	// double	u;
	// double	v;

	// theta = atan2(g->ci.z, g->ci.x);
	// y = g->ci.y;
	// u = theta / (2 * M_PI);
	// v = y / g->h;
	// u -= floor(u);
	// u *= (g->t_width - 1);
	// v *= (g->t_height - 1);
	// g->u = nb_clamp(fabs(u), 0.0, g->t_width - 1);
	// g->v = nb_clamp(fabs(v), 0.0, g->t_height - 1);
}

void	texture_cone_uv(t_tuv *g)
{
	// g->u = atan2(g->ci.x, g->ci.z) / (2 * M_PI) + 0.5;
	// g->v = (g->ci.y + g->h / 2) / g->h;
	// g->u *= (g->t_width - 1);
	// g->v *= (g->t_height - 1);
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
