/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:06:55 by suchua            #+#    #+#             */
/*   Updated: 2023/08/02 18:36:59 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include <stdio.h>

double	cone_base(t_ray ray, t_obj *obj, t_vec3 oc)
{
	double	ray_proj;
	t_vec3	top_center;
	double	t;
	t_vec3	inter;

	top_center = vec3_add(obj->center, vec3_mul(obj->h, obj->dir));
	oc = vec3_sub(top_center, ray.origin);
	ray_proj = vec3_dot(ray.dir, obj->dir);
	if (ray_proj == 0.0f)
		return (INFINITY);
	t = vec3_dot(oc, obj->dir) / ray_proj;
	if (t <= 0.0f || t == INFINITY)
		return (INFINITY);
	inter = vec3_add(ray.origin, vec3_mul(t, ray.dir));
	if (vec3_len(vec3_sub(inter, top_center)) <= obj->d / 2.0)
		return (vec3_len(vec3_sub(inter, ray.origin)));
	return (INFINITY);
}

// a   = D|D - (1+k*k)*(D|V)^2
// b/2 = D|X - (1+k*k)*(D|V)*(X|V)
// c   = X|X - (1+k*k)*(X|V)^2
double	cone_intersection(t_ray ray, t_obj *obj)
{
	t_vec3	oc;
	double	t;
	double	k;
	t_vec3	proj_h;
	double	h;

	oc = vec3_sub(obj->center, ray.origin);
	k = tan(get_radian(obj->cone_angle / 2));
	t = solve_quadratic(
		vec3_dot(ray.dir, ray.dir) - (1 + k * k) * pow(vec3_dot(ray.dir, obj->dir), 2),
		-2 * (vec3_dot(ray.dir, oc) - (1 + k * k) * vec3_dot(ray.dir, obj->dir) * vec3_dot(oc, obj->dir)),
		vec3_dot(oc, oc) - (1 + k * k) * pow(vec3_dot(oc, obj->dir), 2)
	);
	if (t == INFINITY)
		return (INFINITY);
	proj_h = vec3_sub(vec3_add(ray.origin, vec3_mul(t, ray.dir)), obj->center);
	h = vec3_dot(proj_h, obj->dir);
	if (h == obj->h || h <= 0.0)
		return (INFINITY);
	if (h > obj->h)
		return (cone_base(ray, obj, oc));
	return (t);
}
