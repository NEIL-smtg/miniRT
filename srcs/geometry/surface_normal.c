/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_normal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 00:31:05 by suchua            #+#    #+#             */
/*   Updated: 2023/07/20 15:00:51 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"

static t_vec3	get_cy_surface_normal(t_ray ray, t_obj *obj, \
		t_vec3 inter, double t)
{
	t_vec3	oi;
	double	h;
	t_vec3	projection;
	t_vec3	n;

	oi = vec3_sub(inter, obj->center);
	h = vec3_dot(oi, obj->dir);
	projection = vec3_mul(h, obj->dir);
	n = vec3_sub(oi, projection);
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
		// if (vec3_dot(ray.dir, obj->dir) < 0.0f)
		// 	return (vec3_mul(-1, obj->dir));
		return (obj->dir);
	}
	else
		return (get_cy_surface_normal(ray, obj, inter, t));
}
