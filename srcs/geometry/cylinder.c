/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 22:10:26 by suchua            #+#    #+#             */
/*   Updated: 2023/07/04 01:30:24 by suchua           ###   ########.fr       */
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
	t = -vec3_dot(oc, top_normal) / proj_ray_normal;
	if (t < 0.0 || t > obj->h)
		return (INFINITY);
	return (t);
}

double	below_cylinder(t_ray ray, t_obj *obj, t_vec3 oc)
{
	double	t;
	double	proj_ray_normal;

	oc = vec3_sub(obj->center, ray.origin);
	proj_ray_normal = vec3_dot(ray.dir, obj->dir);
	if (proj_ray_normal == 0.0)
		return (INFINITY);
	t = -vec3_dot(oc, obj->dir) / proj_ray_normal;
	if (t < 0.0 || t > obj->h)
		return (INFINITY);
	return (t);
}

double	outside_cylinder(t_ray ray, t_obj *obj, t_cyvars var)
{
	t_vec3	obj_org;
	t_vec3	ray_proj;
	double	height;
	double	distance ;

	obj_org = vec3_sub(obj->center, ray.origin);
	ray_proj = normalize(proj_cto);
	distance = solve_quadratic(vec3_dot(ray_proj, ray_proj), \
					-2 * vec3_dot(proj_cto, ray_proj), \
					vec3_dot(proj_cto, proj_cto) - pow(obj->d / 2, 2));
	if (distance == INFINITY)
		return (INFINITY);
	distance /= vec3_dot(ray.dir, ray_proj);
	height = vec3_dot(vec3_sub(vec3_mul(distance, ray.dir), obj_org), obj->dir);
	if (height == 0 || height == obj->h)
		return (INFINITY);
	else if (height < 0)
		return (below_cylinder(ray, obj, var.oc));
	else if (height > obj->h)
		return (above_cylinder(ray, obj, var.oc));
	return (distance);
}

double	cylinder_intersection(t_ray ray, t_obj *obj)
{
	t_cyvars	var;

	var.oc = vec3_sub(obj->center, ray.origin);
	var.vec_h = vec3_sub(ray.dir, var.oc);
	var.proj_h = vec3_dot(var.vec_h, obj->dir);
	var.vec_r = vec3_cross(obj->dir, vec3_cross(var.vec_h, obj->dir));
	var.proj_r = normalize_divisor(var.vec_r);
	if (var.proj_h == 0.0 || var.proj_h == obj->h \
		|| var.proj_r == obj->d / 2.0)
		return (INFINITY);
	if (var.proj_r > obj->d / 2.0)
		return (outside_cylinder(ray, obj, var));
	if (var.proj_h > obj->h)
		return (above_cylinder(ray, obj, var.oc));
	return (below_cylinder(ray, obj, var.oc));
}
