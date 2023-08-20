/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:56:28 by suchua            #+#    #+#             */
/*   Updated: 2023/08/21 04:01:53 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_handler(t_tuv *g, t_obj *obj, t_vec3 inter, \
		t_img texture)
{
	g->ci = normalize(vec3_sub(inter, obj->center));
	g->r = obj->d / 2.0;
	g->h = obj->h;
	g->t_height = texture.height;
	g->t_width = texture.width;
	g->texture = texture;
}

//	get_right
static t_vec3	get_tangent(t_vec3 n)
{
	// if (vec3_dot(n, new_vec3(0, 1, 0)))
	// 	return (normalize(vec3_cross(n, new_vec3(0, 0, 1))));
	// else
	return (normalize(vec3_cross(n, new_vec3(1, 1, 0))));
}

//	get_up
static t_vec3	get_bitangent(t_vec3 n, t_vec3 t)
{
	return (normalize(vec3_cross(n, t)));
}

t_vec3	get_bump_offset(t_vec3 n, double bump_val)
{
	const double	bump_strength = 0.77;
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

t_rgb	filter_bilinear(t_tuv g);

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
	obj->tx = filter_bilinear(g);
	bump_val = texture.bump_map[(int) g.v][(int) g.u] * 1.618;
	bump_offset = get_bump_offset(n, bump_val);
	perbuted = normalize(vec3_add(n, bump_offset));
	return (perbuted);
}
