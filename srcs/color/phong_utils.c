/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 23:41:18 by suchua            #+#    #+#             */
/*   Updated: 2023/08/14 02:57:17 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	reflect(t_vec3 incident, t_vec3 surface_normal)
{
	double	dot;
	t_vec3	ref;

	dot = vec3_dot(incident, surface_normal);
	ref = vec3_sub(incident, vec3_mul(2.0 * dot, surface_normal));
	return (normalize(ref));
}

t_vec3	refract(t_vec3 incident, t_vec3 surface_normal, double n1, double n2)
{
	double	cos_theta1;
	double	theta1;
	double	sin_theta2;
	double	theta2;
	t_vec3	ref;

	cos_theta1 = vec3_dot(incident, surface_normal);
	theta1 = acos(cos_theta1);
	sin_theta2 = (n1 / n2) * sin(theta1);
	if (sin_theta2 > 1.0)
		return (reflect(incident, surface_normal));
	theta2 = asin(sin_theta2);
	ref = vec3_mul(n1 / n2, incident);
	ref = vec3_sub(ref, vec3_mul(cos(theta2), surface_normal));
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
	light_dir = normalize(vec3_sub(sc.light->pos, inter));
	angle = vec3_dot(
			view_dir,
			reflect(vec3_mul(-1, light_dir), surface_normal)
			);
	angle = fmax(0.0f, angle);
	specular = rgb_scale(sc.light->brightness, sc.light->rgb);
	if (obj->type == PLANE)
		return (rgb_scale(pow(angle, 3), specular));
	specular = rgb_scale(pow(angle, 11), specular);
	return (specular);
}

double	get_diffuse_color(t_light *light, t_vec3 inter, \
	t_vec3 surface_normal)
{	
	double	diff;
	t_vec3	light_dir;

	light_dir = normalize(vec3_sub(light->pos, inter));
	diff = vec3_dot(surface_normal, light_dir);
	return (fmax(diff, 0));
}
