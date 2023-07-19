/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 00:54:18 by suchua            #+#    #+#             */
/*   Updated: 2023/07/19 18:32:51 by suchua           ###   ########.fr       */
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

static t_vec3	reflect(t_vec3 incident, t_vec3 surface_normal)
{
	double	dot;
	t_vec3	ref;

	dot = vec3_dot(incident, surface_normal);
	ref = vec3_sub(incident, vec3_mul(2.0 * dot, surface_normal));
	return (normalize(ref));
}

static t_rgb	get_specular_light(t_scene sc, t_vec3 surface_normal, \
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

static t_rgb	get_diffuse_color(t_light light, t_obj *obj, \
		t_vec3 inter, t_vec3 surface_normal)
{	
	t_vec3	light_dir;
	t_rgb	diffuse;
	double	angle;

	light_dir = normalize(vec3_sub(light.pos, inter));
	angle = vec3_dot(light_dir, surface_normal);
	angle = fmax(0.0f, angle);
	diffuse = rgb_scale(light.brightness, light.rgb);
	diffuse = rgb_scale(angle, diffuse);
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
	specular = get_specular_light(sc, surface_normal, inter, obj);
	if (obj->type == PLANE)
	{
		diffuse = rgb_scale(PL_DIFFUSE_TERM, diffuse);
		specular = rgb_scale(PL_SPECULAR_TERM, specular);
	}
	sc.amblight.rgb = rgb_scale(sc.amblight.ratio, sc.amblight.rgb);
	return (new_rgb(
			sc.amblight.rgb.r + diffuse.r + specular.r + obj->rgb.r,
			sc.amblight.rgb.g + diffuse.g + specular.g + obj->rgb.g,
			sc.amblight.rgb.b + diffuse.b + specular.b + obj->rgb.b
		));
}
