/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:17:13 by mmuhamad          #+#    #+#             */
/*   Updated: 2023/08/01 15:25:28 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdlib.h>

// Adjust num_squares value to control the number of squares
// Calculate the checkerboard pattern by dividing the sphere's
// surface into small squares
// Determine the checkerboard color based on the sum of square indices
// Map the checkerboard pattern to UV coordinates
void	get_sphere_uv(const t_vec3 *point, double *u, double *v, t_obj *obj)
{
	double	normalized_x = (point->x + obj->d / 2.0) / obj->d;
	double	normalized_y = (point->y + obj->d / 2.0) / obj->d;
	double	normalized_z = (point->z + obj->d / 2.0) / obj->d;
	int		num_squares = 1;
	double	square_size = 1.0 / num_squares;
	int u_square = (int)(normalized_x / square_size);
	int v_square = (int)(normalized_y / square_size);
	int w_square = (int)(normalized_z / square_size);
	int sum_indices = u_square + v_square + w_square;
	int is_white_square = sum_indices % 2 == 0;

	*u = 1.0 - normalized_x;
	*v = 1.0 - normalized_y;
}

t_rgb	checkerboard_color(float u, float v)
{
    float	square_size = 0.125;
    int		u_square = (int)(u / square_size);
    int		v_square = (int)(v / square_size);

	if (((u_square + v_square) % 2) == 0)
	{
		return (new_rgb(255, 255, 255));
	}
	return (new_rgb(50, 50, 50));
}

t_rgb	checkerboard(t_viewport *vp, t_ray ray, t_obj *obj, double t)
{
	double	u;
	double	v;
	t_vec3	inter;
	t_vec3	surface_normal;
	double	diffuse;
	t_rgb	specular;
	t_rgb	color;
	t_rgb	amb;

	surface_normal = get_surface_normal(ray, obj, t);
	inter = vec3_add(ray.origin, vec3_mul(t, ray.dir));
	diffuse = get_diffuse_color(vp->scene->light, obj, inter, surface_normal);
	specular = get_specular_light(*vp->scene, surface_normal, inter, obj);
	if (vp->selected->type == SPHERE)
	{
		get_sphere_uv(&inter, &u, &v, obj);
		color = checkerboard_color(u, v);
		if (in_shadows(*vp->scene, inter, obj, diffuse))
			return (new_rgb(0, 0, 0));
		amb = rgb_scale(vp->scene->amblight.ratio, vp->scene->amblight.rgb);
		return (new_rgb(
				amb.r + specular.r + (color.r * diffuse),
				amb.g + specular.g + (color.g * diffuse),
				amb.b + specular.b + (color.b * diffuse)));
	}
	color = new_rgb(0, 0, 0);
	if (in_shadows(*vp->scene, inter, obj, diffuse))
		return (new_rgb(0, 0, 0));
	// amb = rgb_scale(sc.amblight.ratio, sc.amblight.rgb);
	return (new_rgb(
			amb.r + specular.r + (color.r * diffuse),
			amb.g + specular.g + (color.g * diffuse),
			amb.b + specular.b + (color.b * diffuse)));
}
