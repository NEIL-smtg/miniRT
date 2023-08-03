/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 22:10:26 by suchua            #+#    #+#             */
/*   Updated: 2023/08/03 15:18:08 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

double	above_cylinder(t_ray ray, t_obj *obj, t_vec3 oc)
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
		return (t);
	return (INFINITY);
}

double	below_cylinder(t_ray ray, t_obj *obj, t_vec3 oc)
{
	double	ray_proj;
	double	t;
	t_vec3	inter;

	ray_proj = vec3_dot(ray.dir, obj->dir);
	if (ray_proj == 0.0f)
		return (INFINITY);
	t = vec3_dot(oc, obj->dir) / ray_proj;
	if (t <= 0.0f || t == INFINITY)
		return (INFINITY);
	inter = vec3_add(ray.origin, vec3_mul(t, ray.dir));
	if (vec3_len(vec3_sub(inter, obj->center)) <= obj->d / 2.0)
		return (t);
	return (INFINITY);
}

t_vec3	get_projection(t_vec3 v, t_vec3 obj_dir)
{
	t_vec3	proj;

	proj = vec3_cross(v, obj_dir);
	proj = vec3_cross(obj_dir, proj);
	return (proj);
}

double	outside_cylinder(t_ray ray, t_obj *obj, t_vec3 oc)
{
	t_vec3	oc2d;
	double	t;
	double	h;
	t_vec3	inter;
	t_vec3	rd2d;

	rd2d = normalize(get_projection(ray.dir, obj->dir));
	oc2d = (get_projection(oc, obj->dir));
	t = solve_quadratic(
			vec3_dot(rd2d, rd2d),
			-2.0f * vec3_dot(oc2d, rd2d),
			vec3_dot(oc2d, oc2d) - pow(obj->d / 2.0, 2)
			);
	if (t == INFINITY)
		return (INFINITY);
	t /= vec3_dot(rd2d, ray.dir);
	inter = vec3_add(ray.origin, vec3_mul(t, ray.dir));
	h = vec3_dot(vec3_sub(inter, obj->center), obj->dir);
	if (h == 0.0f || h == obj->h)
		return (INFINITY);
	if (h < 0.0f)
		return (below_cylinder(ray, obj, oc));
	if (h > obj->h)
		return (above_cylinder(ray, obj, oc));
	return (t);
}

double	cylinder_intersection(t_ray ray, t_obj *obj)
{
	t_vec3	oc;
	t_vec3	proj_r;
	t_vec3	proj_h;
	double	h;
	double	r;

	oc = vec3_sub(obj->center, ray.origin);
	proj_h = vec3_sub(ray.dir, oc);
	proj_r = get_projection(proj_h, obj->dir);
	h = vec3_dot(proj_h, obj->dir);
	r = vec3_len(proj_r);
	if (r == obj->d / 2.0)
		return (INFINITY);
	if (r < obj->d / 2.0)
	{
		if (h == 0.0f || h == obj->h)
			return (INFINITY);
		if (h < 0.0f)
			return (below_cylinder(ray, obj, oc));
		if (h > obj->h)
			return (above_cylinder(ray, obj, oc));
	}
	return (outside_cylinder(ray, obj, oc));
}
