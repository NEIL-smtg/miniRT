/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:38:03 by mmuhamad          #+#    #+#             */
/*   Updated: 2023/08/09 11:26:29 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	light_intersection(t_ray ray, t_light *obj)
{
	double	dist;
	t_vec3	obj_vec;

	obj_vec = vec3_sub(obj->pos, ray.origin);
	dist = solve_quadratic(
			vec3_dot(ray.dir, ray.dir),
			-2.0f * vec3_dot(obj_vec, ray.dir),
			vec3_dot(obj_vec, obj_vec) - pow(1, 2)
			);
	return (dist);
}

double	light_intersection_obj(t_ray ray, t_obj *obj)
{
	double	dist;
	t_vec3	obj_vec;

	obj_vec = vec3_sub(obj->center, ray.origin);
	dist = solve_quadratic(
			vec3_dot(ray.dir, ray.dir),
			-2.0f * vec3_dot(obj_vec, ray.dir),
			vec3_dot(obj_vec, obj_vec) - pow(1, 2)
			);
	return (dist);
}
