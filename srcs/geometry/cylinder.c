/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 22:10:26 by suchua            #+#    #+#             */
/*   Updated: 2023/07/18 21:37:35 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include <stdio.h>
#include <stdbool.h>

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
	if (t <= 0.0f)
		return (INFINITY);
	inter = vec3_add(ray.origin, vec3_mul(t, ray.dir));
	inter = vec3_sub(ray.origin, inter);
	if (vec3_len(vec3_sub(oc, inter)) <= obj->d / 2.0)
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
	if (t <= 0.0f)
		return (INFINITY);
	inter = vec3_add(ray.origin, vec3_mul(t, ray.dir));
	inter = vec3_sub(ray.origin, inter);
	if (vec3_len(vec3_sub(oc, inter)) <= obj->d / 2.0)
		return (t);
	return (INFINITY);
}

t_vec3	get_ray_proj(t_vec3 raydir, t_vec3 objdir)
{
	t_vec3	ray;

	ray = vec3_cross(raydir, objdir);
	ray = vec3_cross(ray, objdir);
	return (ray);
}

t_vec3	get_oc_proj(t_vec3 oc, t_vec3 objdir)
{
	t_vec3	ray;

	ray = vec3_cross(oc, objdir);
	ray = vec3_cross(ray, objdir);
	return (ray);
}

double	outside_cylinder(t_ray ray, t_obj *obj, t_vec3 rd2d, t_vec3 oc)
{
	t_vec3	oc2d;
	double	t;
	double	h;
	t_vec3	inter;

	rd2d = (get_ray_proj(ray.dir, obj->dir));
	oc2d = (get_oc_proj(oc, obj->dir));
	t = solve_quadratic(
		vec3_dot(rd2d, rd2d),
		-2 * vec3_dot(rd2d, oc2d),
		vec3_dot(oc2d, oc2d) - pow(obj->d / 2.0, 2)
	);
	if (t == INFINITY)
		return (INFINITY);
	t /= vec3_dot(ray.dir, rd2d);
	inter = vec3_add(ray.origin, vec3_mul(t, ray.dir));
	inter = vec3_add(inter, obj->center);
	h = vec3_dot(inter, obj->dir);
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
	t_vec3	rd2d;
	t_vec3	proj_h;
	double	h;
	double	r;

	oc = vec3_sub(obj->center, ray.origin);
	proj_h = vec3_sub(ray.dir, oc);
	rd2d = get_ray_proj(proj_h, obj->dir);
	h = vec3_dot(proj_h, obj->dir);
	r = vec3_len(rd2d);
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
	return (outside_cylinder(ray, obj, rd2d, oc));
}
