/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_normal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 00:31:05 by suchua            #+#    #+#             */
/*   Updated: 2023/07/15 01:51:10 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"

static t_vec3	get_cy_surface_normal(t_ray ray, t_obj *obj, \
		t_vec3 inter, double t)
{
	double	m;
	t_vec3	oc;
	t_vec3	n;

	oc = vec3_sub(obj->center, ray.origin);
	m = vec3_dot(ray.dir, vec3_mul(t, obj->dir));
	m += vec3_dot(oc, obj->dir);
	n = vec3_sub(inter, obj->center);
	n = vec3_sub(n, vec3_mul(m, obj->dir));
	return (normalize(n));	
}

t_vec3	get_surface_normal(t_ray ray, t_obj *obj, double t)
{
	t_vec3	inter;

	inter = vec3_add(ray.origin, vec3_mul(t, ray.dir));
	if (obj->type == SPHERE)
		return (normalize(vec3_sub(inter, obj->center)));
	else if (obj->type == PLANE)
	{
		if (vec3_dot(ray.dir, obj->dir) < 0.0f)
			return (vec3_mul(-1, obj->dir));
		return (obj->dir);
	}
	else
		return (get_cy_surface_normal(ray, obj, inter, t));
}
