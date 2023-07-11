/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 22:10:26 by suchua            #+#    #+#             */
/*   Updated: 2023/07/11 21:21:52 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include <stdio.h>

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
	if (proj_ray_normal == 0.0f)
		return (INFINITY);
	t = vec3_dot(oc, obj->dir) / proj_ray_normal;
	if (t <= 0.0f)
		return (INFINITY);
	// t = vec3_len(vec3_sub(vec3_mul(t, ray.dir), top_center));
	// if (t > obj->d / 2)
	// 	return (INFINITY);
	// return (t);
	t_vec3 intersection = vec3_add(ray.origin, vec3_mul(t, ray.dir));
    double dist = vec3_len(vec3_sub(intersection, top_center));
    if (dist > obj->d / 2.0)
        return INFINITY;
    return t;
}

double	below_cylinder(t_ray ray, t_obj *obj, t_vec3 oc)
{
	double	t;
	double	proj_ray_normal;
	double	proj_r;

	proj_ray_normal = vec3_dot(ray.dir, obj->dir);
	if (proj_ray_normal == 0.0f)
		return (INFINITY);
	t = vec3_dot(oc, obj->dir) / proj_ray_normal;
	if (t <= 0.0f)
		return (INFINITY);
	// proj_r = vec3_len(vec3_sub(vec3_mul(t, ray.dir), oc));
	// if (proj_r > obj->d / 2)
	// 	return (INFINITY);
	// return (t);
	t_vec3 intersection = vec3_add(ray.origin, vec3_mul(t, ray.dir));
    double dist = vec3_len(vec3_sub(intersection, obj->center));
    if (dist > obj->d / 2.0)
        return INFINITY;
    return t;
}

t_vec3	get_ray_projection2d(t_ray ray, t_obj *obj)
{
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;

	forward = obj->dir;
	right = (vec3_cross(ray.dir, forward));
	up = normalize(vec3_cross(forward, right));
	return (up);
}

t_vec3	get_oc_projection2d(t_vec3 oc, t_vec3 obj_dir)
{
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;

	forward = obj_dir;
	right = vec3_cross(oc, obj_dir);
	up = vec3_cross(forward, right);
	return (up);
}

double	cylinder_intersection(t_ray ray, t_obj *obj)
{
	t_vec3	oc;
	t_vec3	rd2d;
	t_vec3	oc2d;
	double	t;

	oc = vec3_sub(obj->center, ray.origin);
	rd2d = get_ray_projection2d(ray, obj);
	oc2d = get_oc_projection2d(oc, obj->dir);
	t = solve_quadratic(
		vec3_dot(rd2d, rd2d),
		-2 * vec3_dot(rd2d, oc2d),
		vec3_dot(oc2d, oc2d) - pow(obj->d / 2.0, 2)
	);
	if (t == INFINITY)
		return (INFINITY);
	t /= vec3_dot(ray.dir, rd2d);

	t_vec3	intersection;
	double	h;
	double	r;
	t_vec3	c;
	t_vec3	oi;

	intersection = vec3_add(ray.origin, vec3_mul(t, ray.dir));
	h = vec3_dot(vec3_sub(intersection, obj->center), obj->dir);
	if (h == 0.0f || h == obj->h)
		return (INFINITY);
	if (h < 0.0f)
		return (below_cylinder(ray, obj, oc));
	if (h > obj->h)  
		return (above_cylinder(ray, obj, oc));
	// oi = vec3_sub(intersection, obj->center);
	// r = vec3_len(vec3_sub(oi, vec3_mul(h, obj->dir)));
	// if (r > obj->d / 2.0)
	// 	return (INFINITY);
	return (t);
}
