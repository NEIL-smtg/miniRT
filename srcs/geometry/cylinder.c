/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 22:10:26 by suchua            #+#    #+#             */
/*   Updated: 2023/07/06 02:48:28 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"

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
	proj_ray_normal = vec3_dot(ray.dir, top_normal);
	if (proj_ray_normal == 0.0)
		return (INFINITY);
	t = vec3_dot(oc, top_normal) / proj_ray_normal;
	if (t <= 0.0f)
		return (INFINITY);
	t = vec3_len(vec3_sub(vec3_mul(t, ray.dir), oc));
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

double	outside_cylinder(t_ray ray, t_obj *obj, t_cyvars var)
{
	t_vec3	norm_ray_proj;
	t_vec3	oc_proj;
	double	t;
	double	h;

	norm_ray_proj = normalize(vec3_cross(obj->dir, vec3_cross(ray.dir, obj->dir)));
	oc_proj = vec3_cross(obj->dir, vec3_cross(var.oc, obj->dir));
	t = solve_quadratic(
		vec3_dot(norm_ray_proj, norm_ray_proj),
		-2 * vec3_dot(norm_ray_proj, oc_proj),
		vec3_dot(oc_proj, oc_proj) - pow(obj->d / 2.0, 2)
	);
	if (t == INFINITY)
		return (INFINITY);
	t /= vec3_dot(ray.dir, norm_ray_proj);
	h = vec3_dot(vec3_sub(vec3_mul(t, ray.dir), var.oc), obj->dir);
	if (h == 0.0f || h == obj->h)
		return (INFINITY);
	if (h < 0.0f)
		return (below_cylinder(ray, obj, var.oc));
	if (h > obj->h)
		return (above_cylinder(ray, obj, var.oc));
	return (t);
}

double	cylinder_intersection(t_ray ray, t_obj *obj)
{
	t_cyvars	var;

	var.oc = vec3_sub(obj->center, ray.origin);
	var.vec_h = vec3_sub(ray.dir, var.oc);
	var.proj_h = vec3_dot(var.vec_h, obj->dir);
	var.vec_r = vec3_cross(obj->dir, vec3_cross(var.vec_h, obj->dir));
	var.proj_r = vec3_len(var.vec_r);
	if (var.proj_r == obj->d / 2)
		return (INFINITY);
	if (var.proj_r < obj->d / 2)
	{
		if (var.proj_h == 0.0 || var.proj_h == obj->h)
			return (INFINITY);
		if (var.proj_h > obj->h)
			return (above_cylinder(ray, obj, var.oc));
		if (var.proj_h < 0.0f)	
			return (below_cylinder(ray, obj, var.oc));
	}
	return (outside_cylinder(ray, obj, var));
}
