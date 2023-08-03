/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_normal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 00:31:05 by suchua            #+#    #+#             */
/*   Updated: 2023/08/03 19:34:36 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"

static t_vec3	get_cy_surface_normal(t_obj *obj, \
		t_vec3 inter, double t)
{
	t_vec3	ci;
	double	h;
	t_vec3	projection;
	t_vec3	n;

	ci = vec3_sub(inter, obj->center);
	h = vec3_dot(ci, obj->dir);
	if (h >= EPS)
		projection = vec3_mul(h, obj->dir);
	else
		projection = vec3_mul(1e6, obj->dir);
	n = vec3_sub(ci, projection);
	return (normalize(n));
}

static t_vec3	get_cone_surface_normal(t_obj *obj, \
		t_vec3 inter, double t)
{
	t_vec3 ci = vec3_sub(inter, obj->center);
	double h = vec3_dot(ci, obj->dir);
	t_vec3 projection = vec3_mul(h, obj->dir);
	t_vec3 n = vec3_sub(ci, projection);
	return normalize(n);
}

t_vec3	get_surface_normal(t_ray ray, t_obj *obj, double t)
{
	t_vec3	inter;

	inter = vec3_add(ray.origin, vec3_mul(t, ray.dir));
	if (obj->type == SPHERE)
		return (normalize(vec3_sub(inter, obj->center)));
	else if (obj->type == PLANE)
		return (obj->dir);
	else if (obj->type == CYLINDER)
		return (get_cy_surface_normal(obj, inter, t));
	else
		return (get_cone_surface_normal(obj, inter, t));
}
