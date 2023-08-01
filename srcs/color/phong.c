/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 00:54:18 by suchua            #+#    #+#             */
/*   Updated: 2023/08/01 15:56:06 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
	1) diffuse = LightColor * LightBrightness * 
	   (LightDirection • SurfaceNormal) * SurfaceColor
	
	2) specularColor = lightColor * lightBrightness *
	   specularStrength * (viewDirection • reflectionDirection) ^ shininess
	
	3) FinalColor = (AmbientColor * ambientRatio + DiffuseColor)
* */

t_vec3	reflect(t_vec3 incident, t_vec3 surface_normal)
{
	double	dot;
	t_vec3	ref;

	dot = vec3_dot(incident, surface_normal);
	ref = vec3_sub(incident, vec3_mul(2.0 * dot, surface_normal));
	return (normalize(ref));
}

t_rgb	get_specular_light(t_scene sc, t_vec3 surface_normal, \
		t_vec3 inter, t_obj *obj)
{
	double	angle;
	t_vec3	view_dir;
	t_vec3	light_dir;
	t_rgb	specular;

	view_dir = normalize(vec3_sub(sc.cam.pos, inter));
	light_dir = normalize(vec3_sub(sc.light.pos, inter));
	angle = vec3_dot(
			view_dir,
			reflect(vec3_mul(-1, light_dir), surface_normal)
			);
	angle = fmax(0.0f, angle);
	specular = rgb_scale(sc.light.brightness, sc.light.rgb);
	if (obj->type == PLANE)
		return (rgb_scale(pow(angle, 3), specular));
	specular = rgb_scale(1.0, specular);
	specular = rgb_scale(pow(angle, 11), specular);
	return (specular);
}

double	get_diffuse_color(t_light light, t_obj *obj, \
		t_vec3 inter, t_vec3 surface_normal)
{	
	double	angle;
	double	diff;
	t_vec3	light_dir;

	light_dir = normalize(vec3_sub(light.pos, inter));
	diff = vec3_dot(surface_normal, light_dir);
	return (fmax(diff, 0));
}

bool	in_shadows(t_scene sc, t_vec3 inter, t_obj *obj, double diffuse)
{
	t_obj	*closest;
	t_ray	ray;
	double	t;

	if (diffuse == 0.0f)
		return (false);
	ray.dir = vec3_sub(sc.light.pos, inter);
	ray.origin = vec3_add(inter, vec3_mul(EPS, ray.dir));
	closest = NULL;
	t = get_closest_obj(ray, sc.obj, &closest);
	if (t != INFINITY)
		return (true);
	return (false);
}

t_rgb	get_ambient_color(t_scene sc, t_obj *obj, t_vec3 inter,
		t_vec3 surface_normal, double diffuse)
{
	t_rgb	amb;

	if (diffuse > 0.0f)
		return (new_rgb(0, 0, 0));
	amb = new_rgb((obj->rgb.r * sc.amblight.ratio) + (sc.amblight.rgb.r * sc.amblight.ratio),
			(obj->rgb.g * sc.amblight.ratio) + (sc.amblight.rgb.g * sc.amblight.ratio),
			(obj->rgb.b * sc.amblight.ratio) + (sc.amblight.rgb.b * sc.amblight.ratio));
	return (amb);
}

t_rgb	phong_shading(t_scene sc, t_ray ray, t_obj *obj, double t)
{
	t_vec3	inter;
	t_vec3	surface_normal;
	double	diffuse;
	t_rgb	specular;
	t_rgb	amb;

	surface_normal = get_surface_normal(ray, obj, t);
	inter = vec3_add(ray.origin, vec3_mul(t, ray.dir));
	diffuse = get_diffuse_color(sc.light, obj, inter, surface_normal);
	specular = get_specular_light(sc, surface_normal, inter, obj);
	if (obj->type == PLANE)
	{
		diffuse *= PL_DIFFUSE_TERM;
		specular = rgb_scale(PL_SPECULAR_TERM, specular);
	}
	if (in_shadows(sc, inter, obj, diffuse))
		return (new_rgb(0, 0, 0));
	// amb = get_ambient_color(sc, obj, inter, surface_normal, diffuse);
	amb = rgb_scale(sc.amblight.ratio, sc.amblight.rgb);
	return (new_rgb(
			amb.r + specular.r + (obj->rgb.r * diffuse),
			amb.g + specular.g + (obj->rgb.g * diffuse),
			amb.b + specular.b + (obj->rgb.b * diffuse)
		));
}
