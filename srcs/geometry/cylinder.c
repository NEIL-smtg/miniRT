/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 22:10:26 by suchua            #+#    #+#             */
/*   Updated: 2023/07/07 22:06:16 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include <stdio.h>

typedef struct s_cyvars
{
	t_vec3	oc;
	t_vec3	vec_h;
	t_vec3	vec_r;
	double	proj_h;
	double	proj_r;
}	t_cyvars;

double	above_cylinder(t_ray ray, t_obj *obj, t_vec3 oc)
{
	t_vec3	top_normal;
	t_vec3	top_center;
	double	t;
	double	proj_ray_normal;

	top_normal = vec3_mul(obj->h, obj->dir);
	top_center = vec3_add(obj->center, top_normal);
	oc = vec3_sub(top_center, ray.origin);
	proj_ray_normal = vec3_dot(ray.dir, obj->dir);
	if (proj_ray_normal == 0.0)
		return (INFINITY);
	t = vec3_dot(oc, obj->dir) / proj_ray_normal;
	if (t <= 0.0f)
		return (INFINITY);
	t = vec3_len(vec3_sub(vec3_mul(t, ray.dir), top_center));
	if (t > obj->d / 2)
		return (INFINITY);
	return (t);
}

double	below_cylinder(t_ray ray, t_obj *obj, t_vec3 oc)
{
	double	t;
	double	proj_ray_normal;
	double	proj_r;

	proj_ray_normal = vec3_dot(ray.dir, obj->dir);
	if (proj_ray_normal == 0.0)
		return (INFINITY);
	t = vec3_dot(oc, obj->dir) / proj_ray_normal;
	if (t <= 0.0f)
		return (INFINITY);
	proj_r = vec3_len(vec3_sub(vec3_mul(t, ray.dir), oc));
	if (proj_r > obj->d / 2)
		return (INFINITY);
	return (proj_r);
}

double verify(double t, t_ray ray, t_obj *obj)
{
	t_vec3	intersection;
	double	r;
	t_vec3	inter_center;
	t_vec3	oi;
	t_vec3	ic_inter;
	double	h;
	
	intersection = vec3_add(ray.origin, vec3_mul(t, ray.dir));
	oi = vec3_sub(intersection, obj->center);
	h = vec3_dot(oi, obj->dir);
	if (h == 0.0f || h == obj->h)
		return (INFINITY);
	if (h < 0.0f)
		return (below_cylinder(ray, obj, vec3_sub(obj->center, ray.origin)));
	if (h > obj->h)
		return (above_cylinder(ray, obj, vec3_sub(obj->center, ray.origin)));
	inter_center = vec3_add(obj->center, vec3_mul(h, obj->dir));
	ic_inter = vec3_sub(intersection, inter_center);
	r = vec3_len(ic_inter);
	// if (r >= obj->d / 2.0)
	// 	return (INFINITY);
	return (t);
}


double	cylinder_intersection(t_ray ray, t_obj *obj)
{
	t_vec3	r;
	t_vec3	oc2d;
	t_vec3	oc;
	double	h;
	double	t;

	r = normalize(vec3_cross(obj->dir, vec3_cross(ray.dir, obj->dir)));
	oc = vec3_sub(obj->center, ray.origin);
	oc2d = vec3_cross(obj->dir, vec3_cross(oc, obj->dir));
	h = vec3_dot(vec3_sub(ray.dir, obj->center), obj->dir);
	if (h == 0.0f || h == obj->h)
		return (INFINITY);
	t = solve_quadratic(
		vec3_dot(r, r),
		-2 * vec3_dot(r, oc2d),
		vec3_dot(oc2d, oc2d) - pow(obj->d / 2.0, 2)
	);
	if (t == INFINITY)
		return (t);
	return (verify(t / vec3_dot(ray.dir, r), ray, obj));
}
