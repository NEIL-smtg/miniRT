/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:06:55 by suchua            #+#    #+#             */
/*   Updated: 2023/08/17 19:10:48 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// a   = D|D - (1+k*k)*(D|V)^2
// b/2 = D|X - (1+k*k)*(D|V)*(X|V)
// c   = X|X - (1+k*k)*(X|V)^2
static double	get_ac_coeff(t_vec3 rd_oc, t_vec3 n, double k)
{
	double	res;

	res = vec3_dot(rd_oc, rd_oc);
	res -= k * pow(vec3_dot(rd_oc, n), 2);
	return (res);
}

static double	get_b_coef(t_vec3 rd, t_vec3 n, t_vec3 oc, double k)
{
	double	res;

	res = vec3_dot(rd, oc);
	res -= k * vec3_dot(rd, n) * vec3_dot(oc, n);
	res *= -2;
	return (res);
}

double	cone_base(t_ray ray, t_obj *obj)
{
	double	ray_proj;
	t_vec3	top_center;
	double	t;
	t_vec3	inter;
	t_vec3	oc;

	top_center = vec3_add(obj->center, vec3_mul(obj->h, obj->dir));
	oc = vec3_sub(top_center, ray.origin);
	ray_proj = vec3_dot(ray.dir, obj->dir);
	if (ray_proj == 0.0)
		return (INFINITY);
	t = vec3_dot(oc, obj->dir) / ray_proj;
	if (t <= EPS || t == INFINITY)
		return (INFINITY);
	inter = vec3_add(vec3_mul(t, ray.dir), ray.origin);
	if (vec3_len(vec3_sub(inter, top_center)) <= obj->d / 2.0)
		return (t);
	return (INFINITY);
}

static double	cone_decider(t_ray ray, double t, t_obj *obj)
{
	t_vec3	inter;
	double	h;
	double	t2;
	t_obj	*close;

	inter = vec3_add(ray.origin, vec3_mul(t, ray.dir));
	h = vec3_dot(vec3_sub(inter, obj->center), obj->dir);
	close = NULL;
	if (h <= 0.0)
	{
		inter = vec3_add(ray.origin, vec3_mul(t, ray.dir));
		ray.origin = vec3_add(inter, vec3_mul(EPS, ray.dir));
		t2 = get_closest_obj(ray, obj, &close, false);
		if (close)
			return (t + t2);
		return (INFINITY);
	}
	if (h > obj->h)
		return (cone_base(ray, obj));
	return (t);
}

double	cone_intersection(t_ray ray, t_obj *obj)
{
	t_vec3	oc;
	double	t;
	double	k;
	t_vec3	proj_h;
	double	h;

	oc = vec3_sub(obj->center, ray.origin);
	proj_h = vec3_sub(ray.dir, oc);
	h = vec3_dot(proj_h, obj->dir);
	if (h >= obj->h - EPS && obj->dir.z > 0.7)
		return (cone_base(ray, obj));
	k = 1 + pow(tan(obj->cone_angle), 2);
	t = solve_quadratic(
			get_ac_coeff(ray.dir, obj->dir, k),
			get_b_coef(ray.dir, obj->dir, oc, k),
			get_ac_coeff(oc, obj->dir, k)
			);
	if (t == INFINITY)
		return (INFINITY);
	return (cone_decider(ray, t, obj));
}
