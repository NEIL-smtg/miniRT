/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_normal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 00:31:05 by suchua            #+#    #+#             */
/*   Updated: 2023/08/22 16:33:25 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef struct s_var
{
	double	cc;
	double	ci;
	t_vec3	co;
	t_vec3	proj;
	double	dot;
	double	d;
}	t_var;

bool	cam_inside_extend(t_obj *obj, t_var *var)
{
	if (obj->type == CYLINDER)
	{
		var->cc = vec3_dot(var->co, obj->dir);
		if (var->cc <= 0.0 || var->cc >= obj->h)
			return (false);
		var->proj = vec3_mul(var->cc, obj->dir);
		var->ci = vec3_len(vec3_sub(var->co, var->proj));
		return (var->ci < obj->d / 2.0);
	}
	else
	{
		var->dot = vec3_dot(var->co, obj->dir);
		var->cc = vec3_len(var->co);
		var->d = tan(obj->cone_angle) * (obj->h - var->cc);
		return (var->dot >= 0.0 && var->dot <= obj->h
			&& var->cc <= obj->h && var->cc <= var->d);
	}
}

//	cc = len of center to camera
//	ci = len of center to intersection
bool	cam_inside(t_ray ray, t_obj *obj, t_vec3 inter)
{
	t_var	var;

	if (obj->type == PLANE)
		return (false);
	var.co = vec3_sub(ray.origin, obj->center);
	if (obj->type == SPHERE)
	{
		var.cc = vec3_len(vec3_sub(ray.origin, obj->center));
		var.ci = vec3_len(vec3_sub(inter, obj->center));
		return (var.cc < var.ci);
	}
	return (cam_inside_extend(obj, &var));
}

static t_vec3	get_cy_surface_normal(t_obj *obj, \
		t_vec3 inter)
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
		n = get_cy_surface_normal(obj, inter);
	if (inside)
		n = vec3_mul(-1.0, n);
	return (get_bump_effect_normal(obj, inter, n, texture));
}
