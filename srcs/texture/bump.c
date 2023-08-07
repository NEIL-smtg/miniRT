/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:56:28 by suchua            #+#    #+#             */
/*   Updated: 2023/08/08 01:08:11 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_handler(t_tuv *g, t_obj *obj, t_vec3 inter, \
		t_img texture)
{
	g->ci = vec3_sub(inter, obj->center);
	g->r = obj->d / 2.0;
	g->h = obj->h;
	g->t_height = texture.height;
	g->t_width = texture.width;
}

static t_vec3	get_tangent(t_vec3 n)
{
	if (n.y >= 0.99)
		return (vec3_cross(n, new_vec3(1, 0, 0)));
	return (vec3_cross(n, new_vec3(0, 1, 0)));
}

static t_vec3	get_bitangent(t_vec3 n, t_vec3 t)
{
	return (normalize(vec3_cross(n, t)));
}

t_vec3	get_bump_offset(t_vec3 n, double bump_val)
{
	const double	bump_strength = 0.5;
	const double	bumping = (bump_val - 0.5) * bump_strength;
	t_vec3			tangent;
	t_vec3			bitangent;
	t_vec3			bump_offset;

	tangent = get_tangent(n);
	bitangent = get_bitangent(n, tangent);
	bump_offset = vec3_mul(bumping, tangent);
	bump_offset = vec3_add(bump_offset, vec3_mul(bumping, bitangent));
	return (bump_offset);
}

t_vec3	get_bump_effect_normal(t_obj *obj, t_vec3 inter, t_vec3 n, \
		t_img texture)
{
	t_tuv	g;
	double	bump_val;
	t_vec3	bump_offset;
	t_vec3	perbuted;

	if (!obj->bump || !texture.ptr)
		return (n);
	init_handler(&g, obj, inter, texture);
	obj->get_uv(&g);
	bump_val = texture.bump_map[(int) g.u][(int) g.v] * 10;
	bump_offset = get_bump_offset(n, bump_val);
	perbuted = normalize(vec3_add(n, bump_offset));
	return (perbuted);
}
