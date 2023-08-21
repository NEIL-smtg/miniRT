/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 00:16:39 by suchua            #+#    #+#             */
/*   Updated: 2023/08/21 12:19:31 by mmuhamad         ###   ########.fr       */
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

double	fresnel_schlick(double cos_theta, double n1, double n2)
{
    double r0 = (n1 - n2) / (n1 + n2);
    r0 = r0 * r0;
    return (r0 + (1.0 - r0) * pow(1.0 - cos_theta, 5.0));
}

double	fresnel(double cos_theta, double n1, double n2)
{
    // Using the Schlick approximation
    return fresnel_schlick(cos_theta, n1, n2);
}

//	n1 = refractive index of ray is coming from
//	n1 = refractive index of ray is entering
t_vec3	refract(t_vec3 surface_normal, t_vec3 incident, double n1, double n2)
{
	double	n;
	double	cos_theta1;
	double	cos_theta2;	
	double	sin_theta2;
	t_vec3	refr;

	cos_theta1 = vec3_dot(incident, surface_normal);
	n = n1 / n2;
	if (cos_theta1 < 0.0)
	{
		surface_normal = vec3_mul(-1.0, surface_normal);
		cos_theta1 = -cos_theta1;
		n = n2 / n1;
	}
	sin_theta2 = n * sqrt(1.0 - pow(cos_theta1, 2));
	if (sin_theta2 >= 1.0)
		return reflect(incident, surface_normal);
	cos_theta2 = sqrt(1.0 - pow(sin_theta2, 2));
	refr = vec3_mul(n, incident);
	refr = vec3_add(refr, vec3_mul(n * cos_theta1 - cos_theta2, surface_normal));
	return (normalize(refr));
}

enum e_ref
{
	REFLECT,
	REFRACT
};

typedef struct s_bounce
{
	t_vec3		inter;
	t_vec3		surface_normal;
	t_viewport	*vp;
	t_ray		ray;
	t_obj		*objlst;
	t_rgb		color;
	t_obj		*closest;
	double		n1;
	double		n2;
}	t_bounce;

t_rgb	start_bouncing(t_bounce b, int depth, enum e_ref type)
{
	double	t;
	double	attenuation;

	if (depth == 0)
		return (b.color);
	b.ray.dir = normalize(vec3_sub(b.inter, b.vp->scene->cam.pos));
	if (type == REFLECT)
		b.ray.dir = reflect(b.ray.dir, b.surface_normal);
	else
		b.ray.dir = refract(b.surface_normal, b.ray.dir, b.n1, b.n2);
	b.ray.origin = vec3_add(b.inter, vec3_mul(EPS, b.ray.dir));
	b.closest = NULL;

	t = get_closest_obj(b.ray, b.objlst, &b.closest, false);
	if (!b.closest)
		return (b.color);
	b.n1 = b.n2;
	if (b.closest->type == SPHERE)
		b.n2 = 1.4;
	else
		b.n2 = 1.0;
	b.surface_normal = get_surface_normal(b.ray, b.closest, t, b.vp->texture);
	b.inter = vec3_add(b.ray.origin, vec3_mul(t, b.ray.dir));
	attenuation = pow(0.8, depth);
	if (b.closest->type == SPHERE)
		attenuation *= 0.9;
	else
		attenuation *= 0.15;
	b.color = rgb_add(b.color, rgb_scale(attenuation, b.closest->rgb));
	return (start_bouncing(b, depth - 1, type));
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
	amb = rgb_scale(1.8, amb);
	diffuse = get_diffuse_color(vp->scene->light, b.inter, b.surface_normal);
	// if (diffuse == 0.0)
	// 	return (amb);
	color = rgb_add(amb, rgb_scale(diffuse, obj->rgb));
	color = rgb_add(color, start_bouncing(b, 1, REFLECT));
	return (color);
}

t_rgb	transparent(t_vec3 surface_normal, t_vec3 inter, t_viewport *vp, t_obj *obj)
{
	t_bounce	b;
	t_rgb		color;
	t_rgb		amb;
	double		diffuse;

	b.inter = inter;
	b.color = new_rgb(0, 0, 0);
	b.vp = vp;
	b.surface_normal = surface_normal;
	b.objlst = vp->scene->obj;
	b.n1 = 1.0;
	b.n2 = 1.4;

	t_rgb c1 = start_bouncing(b, 1, REFLECT);
	t_rgb c2 = start_bouncing(b, 1, REFRACT);
	amb = get_ambient_color(vp->scene->amblight, obj->rgb);

	color = rgb_add_3(c1, c2, amb);
	return (color);
}
