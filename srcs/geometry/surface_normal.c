/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_normal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 00:31:05 by suchua            #+#    #+#             */
/*   Updated: 2023/08/02 17:27:39 by suchua           ###   ########.fr       */
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

//	N = nrm( P-C - (1+k*k)*V*m )
static t_vec3	get_cone_surface_normal(t_ray ray, t_obj *obj, \
		t_vec3 inter, double t)
{
	t_vec3	n;
	double	k;
	t_vec3	oc;
	double	m;

	k = tan(get_radian(obj->cone_angle / 2));
	k = 1 + k * k;
	n = vec3_sub(inter, obj->center);
	m = obj->d / 2.0 / k;
	n = vec3_sub(n, vec3_mul(k * m, obj->dir));
	return (normalize(n));
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
		return (get_cy_surface_normal(ray, obj, inter, t));
	else
		return (get_cone_surface_normal(ray, obj, inter, t));
}
