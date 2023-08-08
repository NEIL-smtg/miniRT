/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_normal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 00:31:05 by suchua            #+#    #+#             */
/*   Updated: 2023/08/08 18:36:56 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	get_cy_surface_normal(t_obj *obj, \
		t_vec3 inter, double t)
{
	t_vec3	ci;
	double	h;
	t_vec3	projection;
	t_vec3	n;

	ci = vec3_sub(inter, obj->center);
	h = vec3_dot(ci, obj->dir);
	projection = vec3_mul(h, obj->dir);
	n = vec3_sub(ci, projection);
	return (normalize(n));
}

t_vec3	get_surface_normal(t_ray ray, t_obj *obj, double t, t_img texture)
{
	t_vec3	inter;
	t_vec3	n;

	inter = vec3_add(ray.origin, vec3_mul(t, ray.dir));
	if (obj->type == SPHERE)
		n = normalize(vec3_sub(inter, obj->center));
	else if (obj->type == PLANE)
		n = obj->dir;
	else
		n = get_cy_surface_normal(obj, inter, t);
	return (get_bump_effect_normal(obj, inter, n, texture));
}
