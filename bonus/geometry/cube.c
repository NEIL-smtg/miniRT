/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:38:03 by mmuhamad          #+#    #+#             */
/*   Updated: 2023/08/10 00:29:26 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//	light render in cube shape is better
double	cube_intersection(t_ray ray, t_light *light)
{
	const double	cube_length = 0.75;
	t_vec3			min;
	t_vec3			max;
	double			t_enter;
	double			t_exit;

	min.x = (light->pos.x - cube_length / 2.0 - ray.origin.x) / ray.dir.x;
	max.x = (light->pos.x + cube_length / 2.0 - ray.origin.x) / ray.dir.x;
	min.y = (light->pos.y - cube_length / 2.0 - ray.origin.y) / ray.dir.y;
	max.y = (light->pos.y + cube_length / 2.0 - ray.origin.y) / ray.dir.y;
	min.z = (light->pos.z - cube_length / 2.0 - ray.origin.z) / ray.dir.z;
	max.z = (light->pos.z + cube_length / 2.0 - ray.origin.z) / ray.dir.z;
	t_enter = fmax(
			fmax(fmin(min.x, max.x), fmin(min.y, max.y)),
			fmin(min.z, max.z)
			);
	t_exit = fmin(
			fmin(fmax(min.x, max.x), fmax(min.y, max.y)),
			fmax(min.z, max.z)
			);
	if (t_enter > t_exit || t_exit <= EPS)
		return (INFINITY);
	return (t_enter);
}

double	cube_intersection_obj(t_ray ray, t_obj *obj)
{
	const double	cube_length = 0.75;
	t_vec3			min;
	t_vec3			max;
	double			t_enter;
	double			t_exit;

	min.x = (obj->center.x - cube_length / 2.0 - ray.origin.x) / ray.dir.x;
	max.x = (obj->center.x + cube_length / 2.0 - ray.origin.x) / ray.dir.x;
	min.y = (obj->center.y - cube_length / 2.0 - ray.origin.y) / ray.dir.y;
	max.y = (obj->center.y + cube_length / 2.0 - ray.origin.y) / ray.dir.y;
	min.z = (obj->center.z - cube_length / 2.0 - ray.origin.z) / ray.dir.z;
	max.z = (obj->center.z + cube_length / 2.0 - ray.origin.z) / ray.dir.z;
	t_enter = fmax(
			fmax(fmin(min.x, max.x), fmin(min.y, max.y)),
			fmin(min.z, max.z)
			);
	t_exit = fmin(
			fmin(fmax(min.x, max.x), fmax(min.y, max.y)),
			fmax(min.z, max.z)
			);
	if (t_enter > t_exit || t_exit <= EPS)
		return (INFINITY);
	return (t_enter);
}
