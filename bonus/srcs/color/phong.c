/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 00:54:18 by suchua            #+#    #+#             */
/*   Updated: 2023/08/16 19:09:40 by mmuhamad         ###   ########.fr       */
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

t_rgb	get_ambient_color(t_amblight amb, t_rgb color)
{
	t_rgb	a;
	double	ratio;

	ratio = amb.ratio * 0.15;
	a = rgb_scale(ratio, rgb_add(color, amb.rgb));
	return (a);
}

t_rgb	get_phong_color(t_scene sc, t_obj *obj, t_vec3 inter, \
		t_vec3 surface_normal)
{
	double	diffuse;
	t_rgb	specular;
	t_rgb	amb;

	diffuse = get_diffuse_color(sc.light, inter, surface_normal);
	specular = get_specular_light(sc, surface_normal, inter, obj);
	amb = get_ambient_color(sc.amblight, obj->rgb);
	return (rgb_add_3(amb, specular, rgb_scale(diffuse, obj->rgb)));
}

t_rgb	transparent(t_obj *obj, t_vec3 surface_normal, t_scene sc, t_vec3 inter);

t_rgb	phong_shading(t_viewport *vp, t_ray ray, t_obj *obj, double t)
{
	// return (bounce(vp, ray, obj, t));
	t_vec3	inter;
	t_vec3	surface_normal;
	t_rgb	final;
	double	diffuse;
	t_scene	sc;

	final = new_rgb(0, 0, 0);
	surface_normal = get_surface_normal(ray, obj, t, vp->texture);
	inter = vec3_add(ray.origin, vec3_mul(t, ray.dir));
	sc = *vp->scene;
	while (sc.light)
	{
		diffuse = get_diffuse_color(sc.light, inter, surface_normal);
		if (in_shadows(sc, inter, obj, diffuse))
			return (get_ambient_color(sc.amblight, obj->rgb));
		final = rgb_add(
				final,
				get_phong_color(sc, obj, inter, surface_normal));
		sc.light = sc.light->next;
	}
	return (final);
}
