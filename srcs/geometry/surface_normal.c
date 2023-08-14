/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_normal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 00:31:05 by suchua            #+#    #+#             */
/*   Updated: 2023/08/14 21:43:48 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//	cc = len of center to camera
//	ci = len of center to intersection
bool	cam_inside(t_ray ray, t_obj *obj, t_vec3 inter)
{
	double	cc;
	double	ci;
	t_vec3	co;
	t_vec3	proj;

	if (obj->type == PLANE)
		return (false);
	co = vec3_sub(ray.origin, obj->center);
	if (obj->type == SPHERE)
	{
		cc = vec3_len(vec3_sub(ray.origin, obj->center));
		ci = vec3_len(vec3_sub(inter, obj->center));
		return (cc < ci);
	}
	else if (obj->type == CYLINDER)
	{
		cc = vec3_dot(co, obj->dir);
		if (cc <= 0.0 || cc >= obj->h)
			return (false);
		proj = vec3_mul(cc, obj->dir);
		ci = vec3_len(vec3_sub(co, proj));
		return (ci < obj->d / 2.0);
	}
	else
	{
		double dot = vec3_dot(co, obj->dir);
		cc = vec3_len(co);
		double d = tan(obj->cone_angle) * (obj->h - cc);
		return (dot >= 0.0 && dot <= obj->h && cc <= obj->h && cc <= d);
	}
}

static t_vec3	get_cy_surface_normal(t_obj *obj, \
		t_vec3 inter, double t)
{
	t_vec3	ci;
	double	h;
	t_vec3	projection;
	t_vec3	n;

	ci = vec3_sub(inter, obj->center);
	h = vec3_dot(ci, obj->dir);
	if (h >= obj->h - EPS)
		return (obj->dir);
	if (h <= EPS) 
		return (vec3_mul(-1.0, obj->dir));
	projection = vec3_mul(h, obj->dir);
	n = vec3_sub(ci, projection);
	return (normalize(n));
}

t_vec3	get_surface_normal(t_ray ray, t_obj *obj, double t, t_img texture)
{
	t_vec3	inter;
	t_vec3	n;
	bool	inside;

	inter = vec3_add(ray.origin, vec3_mul(t, ray.dir));
	inside = cam_inside(ray, obj, inter);
	if (obj->type == SPHERE)
		n = normalize(vec3_sub(inter, obj->center));
	else if (obj->type == PLANE)
	{
		if (obj->center.x >= EPS)
			n = obj->dir;
		else
			n = vec3_mul(-1.0, obj->dir);
	}
	else
		n = get_cy_surface_normal(obj, inter, t);
	if (inside)
		n = vec3_mul(-1.0, n);
	return (get_bump_effect_normal(obj, inter, n, texture));
}
