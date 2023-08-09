/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 00:54:18 by suchua            #+#    #+#             */
/*   Updated: 2023/08/09 21:34:35 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
	1) diffuse = LightColor * LightBrightness * 
		(LightDirection • SurfaceNormal) * SurfaceColor
	
	2) specularColor = lightColor * lightBrightness *
		specularStrength * (viewDirection • reflectionDirection) ^ shininess
	
	3) FinalColor = ( ((ObjColor + ambientColor) * ambientRatio) +
		specularColor + DiffuseColor )
* */

static t_rgb	get_ambient_color(t_scene sc, t_obj *obj)
{
	t_rgb	amb;
	double	ratio;

	ratio = sc.amblight.ratio * 0.15;
	amb = rgb_scale(ratio, rgb_add(obj->rgb, sc.amblight.rgb));
	return (amb);
}

t_rgb	get_phong_color(t_scene sc, t_obj *obj, t_vec3 inter, \
		t_vec3 surface_normal)
{
	double	diffuse;
	t_rgb	specular;
	t_rgb	amb;

	diffuse = get_diffuse_color(sc.light, inter, surface_normal);
	specular = get_specular_light(sc, surface_normal, inter, obj);
	amb = get_ambient_color(sc, obj);
	return (rgb_add_3(amb, specular, rgb_scale(diffuse, obj->rgb)));
}

t_rgb	phong_shading(t_viewport *vp, t_ray ray, t_obj *obj, double t)
{
	t_vec3	inter;
	t_vec3	surface_normal;
	t_rgb	final_color;
	double	diffuse;
	t_scene	sc;

	final_color = new_rgb(0, 0, 0);
	surface_normal = get_surface_normal(ray, obj, t, vp->texture);
	inter = vec3_add(ray.origin, vec3_mul(t, ray.dir));
	sc = *vp->scene;
	while (sc.light)
	{
		diffuse = get_diffuse_color(sc.light, inter, surface_normal);
		// if (in_shadows(sc, inter, obj, diffuse))
		// 	return (get_ambient_color(sc, obj));
		final_color = rgb_add(
				final_color,
				get_phong_color(sc, obj, inter, surface_normal)
				);
		sc.light = sc.light->next;
	}
	return (final_color);
}
