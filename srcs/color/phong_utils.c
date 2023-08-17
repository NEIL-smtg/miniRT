/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 23:41:18 by suchua            #+#    #+#             */
/*   Updated: 2023/08/16 17:44:27 by mmuhamad         ###   ########.fr       */
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
	// double	cos_theta1;
	// double	theta1;
	// double	sin_theta2;
	// double	theta2;
	// t_vec3	ref;

	// cos_theta1 = vec3_dot(incident, surface_normal);
	// theta1 = acos(cos_theta1);
	// sin_theta2 = (n1 / n2) * sin(theta1);
	// if (sin_theta2 > 1.0)
	// 	return (reflect(incident, surface_normal));
	// theta2 = asin(sin_theta2);
	// ref = vec3_mul(n1 / n2, incident);
	// ref = vec3_sub(ref, vec3_mul(cos(theta2), surface_normal));
	// return (normalize(ref));

	double cos_theta1 = vec3_dot(incident, surface_normal);
    double n = n1 / n2;

    if (cos_theta1 < 0.0)
    {
        surface_normal = vec3_mul(-1.0, surface_normal);
        cos_theta1 = -cos_theta1;
        n = n2 / n1;
    }

    double sin_theta2 = n * sqrt(1.0 - cos_theta1 * cos_theta1);

    if (sin_theta2 >= 1.0)
        return reflect(incident, surface_normal);

    double cos_theta2 = sqrt(1.0 - sin_theta2 * sin_theta2);
    t_vec3 ref = vec3_sub(vec3_mul(n, incident), vec3_mul(n * cos_theta2 - cos_theta1, surface_normal));
    return normalize(ref);
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

double	fresnel(t_vec3 normal, t_vec3 incident_dir, double n1, double n2)
{
    double cos_theta_i = -vec3_dot(incident_dir, normal);
    double sin_theta_t = (n1 / n2) * sqrt(1.0 - cos_theta_i * cos_theta_i);

    if (sin_theta_t >= 1.0) {
        // Total internal reflection
        return 1.0;
    }

    double cos_theta_t = sqrt(1.0 - sin_theta_t * sin_theta_t);

    // Fresnel equations for unpolarized light (average of p- and s-polarizations)
    double r_parallel = ((n2 * cos_theta_i) - (n1 * cos_theta_t)) / ((n2 * cos_theta_i) + (n1 * cos_theta_t));
    double r_perpendicular = ((n1 * cos_theta_i) - (n2 * cos_theta_t)) / ((n1 * cos_theta_i) + (n2 * cos_theta_t));

    return (r_parallel * r_parallel + r_perpendicular * r_perpendicular) / 2.0;
}


// Vacuum or Air: n ≈ 1.0000 (Reference value)
// Gases (e.g., Air): n ≈ 1.0001 - 1.0003
// Glass: n ≈ 1.4 - 1.7 (varies with type)
// Water: n ≈ 1.33
// Diamond: n ≈ 2.42
// Plastics: n ≈ 1.4 - 1.7 (varies with type)
// Metals: n ≈ 0.1 - 3.0 (varies with type and wavelength)
t_rgb	transparent(t_obj *obj, t_vec3 surface_normal, t_scene sc, t_vec3 inter)
{
	t_vec3	refl;
	t_vec3	refr;
	t_vec3	light_dir;
	double	refl_amount;
	double	refr_amount;
	t_rgb	refl_color;
	t_rgb	refr_color;
	t_obj	*o;
	t_ray	ray;

	light_dir = normalize(vec3_sub(sc.light->pos, inter));
	refl = reflect(vec3_mul(-1, light_dir), surface_normal);
	refr = refract(vec3_mul(-1, light_dir), surface_normal, 1.5, 2.0);
	refl_amount = fresnel(surface_normal, vec3_mul(-1, light_dir), 1.5, 2.0);
	refr_amount = 1.0 - refl_amount;

	o = NULL;
	ray.dir = refr;
	ray.origin = vec3_add(inter, vec3_mul(EPS, ray.dir));
	get_closest_obj(ray, sc.obj, &o, false);
	if (o == NULL)
		refr_color = new_rgb(0, 0, 0);
	else
		refr_color = o->rgb;

	while (1)
	{
		o = NULL;
		ray.dir = refl;
		ray.origin = vec3_add(inter, vec3_mul(EPS, ray.dir));
		get_closest_obj(ray, sc.obj, &o, false);
		if (o == NULL)
			refl_color = new_rgb(0, 0, 0);
		else
			refl_color = o->rgb;
		if (o == NULL)
			break ;
	}
	refl_color = rgb_scale(refl_amount, refl_color);
	refr_color = rgb_scale(refr_amount, refr_color);
	return (rgb_add(refl_color, refr_color));
}
