/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 22:10:26 by suchua            #+#    #+#             */
/*   Updated: 2023/07/18 01:07:27 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include <stdio.h>

double	above_cylinder(t_ray ray, t_obj *obj)
{
	t_vec3	center;
	t_vec3	intersection;
	double	dist;

	center = vec3_sub(obj->center, ray.origin);
	center = vec3_add(center, vec3_mul(obj->h, obj->dir));
	if (vec3_dot(ray.dir, obj->dir) == 0)
		return (INFINITY);
	dist = vec3_dot(center, obj->dir) / vec3_dot(ray.dir, obj->dir);
	if (dist <= 0)
		return (INFINITY);
	intersection = vec3_mul(dist, ray.dir);
	if (vec3_len(vec3_sub(intersection, center)) > obj->d / 2.0)
		return (INFINITY);
	return (vec3_len(intersection));
}

double	below_cylinder(t_ray ray, t_obj *obj)
{
	const t_vec3	center = vec3_sub(obj->center, ray.origin);
	const double	dist = vec3_dot(center, obj->dir) / vec3_dot(ray.dir, obj->dir);
	const t_vec3	intersection = vec3_mul(dist, ray.dir);

	if (vec3_dot(ray.dir, obj->dir) == 0)
		return (INFINITY);
	if (dist <= 0)
		return (INFINITY);
	if (vec3_len(vec3_sub(intersection, center)) > obj->d / 2.0)
		return (INFINITY);
	return (vec3_len(intersection));
}

double	outside_cylinder(t_ray ray, t_obj *obj)
{
	const t_vec3	obj_org = vec3_sub(obj->center, ray.origin);
	const t_vec3	ray_proj = normalize(\
								vec3_cross(obj->dir, vec3_cross(ray.dir, obj->dir)));
	const t_vec3	org_proj = vec3_cross(obj->dir, vec3_cross(obj_org, obj->dir));
	double			height;
	double			distance ;

	distance = solve_quadratic(vec3_dot(ray_proj, ray_proj), \
					-2 * vec3_dot(org_proj, ray_proj), \
					vec3_dot(org_proj, org_proj) - pow(obj->d / 2.0, 2));
	if (distance == INFINITY)
		return (INFINITY);
	distance /= vec3_dot(ray.dir, ray_proj);
	height = vec3_dot(vec3_sub(vec3_mul(distance, ray.dir), obj_org), obj->dir);
	if (height == 0 || height == obj->h)
		return (INFINITY);
	else if (height < 0)
		return (below_cylinder(ray, obj));
	else if (height > obj->h)
		return (above_cylinder(ray, obj));
	return (distance);
}

double	cylinder_intersection(t_ray ray, t_obj *obj)
{
	const t_vec3	obj_org = vec3_sub(obj->center, ray.origin);
	const t_vec3	cam_from_cy = vec3_sub(ray.dir, obj_org);
	const t_vec3	cam_from_cy_proj = vec3_cross(obj->dir, \
										vec3_cross(cam_from_cy, obj->dir));
	const double	dist = vec3_len(cam_from_cy_proj);
	const double	height = vec3_dot(cam_from_cy, obj->dir);

	if (dist == obj->d / 2.0)
		return (INFINITY);
	else if (dist < obj->d / 2.0)
	{
		if (height == 0 || height == obj->h)
			return (INFINITY);
		else if (height < 0)
			return (below_cylinder(ray, obj));
		else if (height > obj->h)
			return (above_cylinder(ray, obj));
	}
	return (outside_cylinder(ray, obj));
}