/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:12:55 by mmuhamad          #+#    #+#             */
/*   Updated: 2023/08/22 16:58:56 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_uv_square(int *u_square, int *v_square, t_vec2	*uv, t_obj *obj)
{
	double	square_size;

	if (obj->type == CYLINDER || obj->type == CONE)
	{
		square_size = 0.2f;
		*u_square = floor(uv->u / square_size);
		*v_square = floor(uv->v / square_size);
	}
	else if (obj->type == PLANE)
	{
		square_size = EPS;
		*u_square = floor(uv->u * square_size);
		*v_square = floor(uv->v * square_size);
	}
}

t_rgb	checkerboard_color(float u, float v, t_obj *obj)
{
	int		u_square;
	int		v_square;
	t_vec2	uv;

	uv.u = u;
	uv.v = v;
	if (obj->type == SPHERE)
	{
		if ((((int)u + (int)v) % 2) == 0)
			return (new_rgb(255, 255, 255));
		return (new_rgb(50, 50, 50));
	}
	get_uv_square(&u_square, &v_square, &uv, obj);
	if (((u_square + v_square) % 2) == 0)
		return (new_rgb(255, 255, 255));
	return (new_rgb(0, 0, 0));
}

t_rgb	checkerboard_extend(t_stuff	*stuff, t_obj *obj, t_tuv *g)
{
	t_vec2	uv;

	if (obj->checkerboard && obj->type == PLANE)
		get_plane_uv(&stuff->inter, &uv.u, &uv.v);
	else if (obj->checkerboard && obj->type == CYLINDER)
		get_cylinder_uv(&stuff->inter, &uv.u, &uv.v, obj);
	else if (obj->checkerboard && obj->type == CONE)
		get_sphere_uv(&stuff->inter, &uv.u, &uv.v, obj);
	if (obj->type == SPHERE)
		return (checkerboard_color(g->u, g->v, obj));
	else
		return (checkerboard_color(uv.u, uv.v, obj));
}
