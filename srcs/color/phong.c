/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 00:54:18 by suchua            #+#    #+#             */
/*   Updated: 2023/07/19 00:37:27 by suchua           ###   ########.fr       */
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

static double	get_ambient(t_amblight am, char type)
{
	if (type == 'r')
		return (am.rgb.r * am.ratio);
	else if (type == 'g')
		return (am.rgb.g * am.ratio);
	else
		return (am.rgb.b * am.ratio);
}

static t_vec3	reflect(t_vec3 incident, t_vec3 surface_normal)
{
	double	dot;
	t_vec3	ref;

	dot = vec3_dot(incident, surface_normal);
	ref = vec3_sub(incident, vec3_mul(2.0 * dot, surface_normal));
	return (normalize(ref));
}

static t_rgb	get_specular_light(t_scene sc, t_vec3 surface_normal, \
		t_vec3 inter, t_rgb obj)
{
	double	angle;
	t_vec3	view_dir;
	t_vec3	light_dir;
	double	term;

	view_dir = normalize(vec3_sub(sc.cam.pos, inter));
	light_dir = normalize(vec3_sub(sc.light.pos, inter));
	angle = vec3_dot(
			view_dir,
			reflect(vec3_mul(-1, light_dir), surface_normal)
			);
	angle = fmax(0.0f, angle);
	return (new_rgb(
			sc.light.rgb.r * sc.light.brightness * 1.0 * pow(angle, 11),
			sc.light.rgb.g * sc.light.brightness * 1.0 * pow(angle, 11),
			sc.light.rgb.b * sc.light.brightness * 1.0 * pow(angle, 11)
		));
}

static t_rgb	get_diffuse_color(t_light light, t_obj *obj, \
		t_vec3 inter, t_vec3 surface_normal)
{	
	t_vec3	light_dir;
	t_rgb	diffuse;
	double	angle;

	light_dir = normalize(vec3_sub(light.pos, inter));
	angle = vec3_dot(light_dir, surface_normal);
	angle = fmax(0.0f, angle);
	diffuse.r = light.rgb.r * light.brightness * angle;
	diffuse.g = light.rgb.g * light.brightness * angle;
	diffuse.b = light.rgb.b * light.brightness * angle;
	return (diffuse);
}

t_rgb	phong_shading(t_scene sc, t_ray ray, t_obj *obj, double t)
{
	t_vec3	inter;
	t_vec3	surface_normal;
	t_rgb	diffuse;
	t_rgb	specular;

	surface_normal = get_surface_normal(ray, obj, t);
	inter = vec3_add(ray.origin, vec3_mul(t, ray.dir));
	diffuse = get_diffuse_color(sc.light, obj, inter, surface_normal);
	specular = get_specular_light(sc, surface_normal, inter, obj->rgb);
	if (obj->type == PLANE)
	{
		diffuse.r *= DIFFUSE_TERM;
		diffuse.g *= DIFFUSE_TERM;
		diffuse.b *= DIFFUSE_TERM;
	}
	return (new_rgb(
			get_ambient(sc.amblight, 'r') + diffuse.r + specular.r + obj->rgb.r,
			get_ambient(sc.amblight, 'g') + diffuse.g + specular.g + obj->rgb.g,
			get_ambient(sc.amblight, 'b') + diffuse.b + specular.b + obj->rgb.b
		));
}
