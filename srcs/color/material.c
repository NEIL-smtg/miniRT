/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 00:16:39 by suchua            #+#    #+#             */
/*   Updated: 2023/08/16 17:47:05 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <time.h>

double	randfrom(double min, double max)
{
	double	range;
	double	div;

	range = (max - min);
	div = RAND_MAX / range;
	return (min + rand() / div);
}

typedef struct s_bounce
{
	t_vec3		inter;
	t_vec3		surface_normal;
	t_viewport	*vp;
	t_ray		ray;
	t_obj		*objlst;
	t_rgb		color;
	t_obj		*closest;
}	t_bounce;

t_rgb	start_bouncing(t_bounce b, int depth)
{
	double	t;
	double	attenuation;

	if (depth == 0)
		return (b.color);
	b.ray.dir = normalize(vec3_sub(b.vp->scene->light->pos, b.inter));
	b.ray.dir = vec3_mul(-1.0, b.ray.dir);
	b.ray.dir = normalize(reflect(b.ray.dir, b.surface_normal));
	b.ray.origin = vec3_add(b.inter, vec3_mul(EPS, b.ray.dir));
	b.closest = NULL;
	t = get_closest_obj(b.ray, b.objlst, &b.closest, false);
	if (!b.closest)
		return (b.color);
	b.surface_normal = get_surface_normal(b.ray, b.closest, t, b.vp->texture);
	b.inter = vec3_add(b.ray.origin, vec3_mul(t, b.ray.dir));
	attenuation = pow(0.8, depth) * 0.3;
	b.color = rgb_add(b.color, rgb_scale(attenuation, b.closest->rgb));

	// b.color = clamp(b.color, 0.0, 100.0);
    // b.color = rgb_scale(attenuation, b.color);

	return (start_bouncing(b, depth - 1));
}

t_rgb	bounce(t_viewport *vp, t_ray ray, t_obj *obj, double t)
{
	t_bounce	b;
	t_rgb		color;
	t_rgb		amb;
	double		diffuse;

	b.inter = vec3_add(ray.origin, vec3_mul(t, ray.dir));
	b.color = new_rgb(0, 0, 0);
	b.vp = vp;
	b.surface_normal = get_surface_normal(ray, obj, t, vp->texture);
	b.objlst = vp->scene->obj;
	amb = get_ambient_color(vp->scene->amblight, obj->rgb);
	diffuse = get_diffuse_color(vp->scene->light, b.inter, b.surface_normal);
	if (diffuse <= EPS)
		return (amb);
	color = rgb_add(amb, rgb_scale(diffuse, obj->rgb));
	color = rgb_add(color, start_bouncing(b, 1));
	return (color);
}
