/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 15:11:48 by suchua            #+#    #+#             */
/*   Updated: 2023/07/02 01:28:32 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"

double	solve_quadratic(double a, double b, double c)
{
	double	discriminant;
	double	t1;
	double	t2;

	discriminant = pow(b, 2) - 4.0 * a * c;
	if (discriminant <= 0.0f || (2.0 * a) <= 1e-6)
		return (INFINITY);
	t1 = (-b - sqrt(discriminant) / (2.0 * a));
	t2 = (-b + sqrt(discriminant) / (2.0 * a));
	if (t1 > 0.0f && t2 > 0.0f && t1 < t2)
		return (t1);
	if (t1 > 0.0f && t2 > 0.0f && t2 < t1)
		return (t2);
	if (t1 > 0.0f)
		return (t1);
	if (t2 > 0.0f)
		return (t2);
	return (INFINITY);
}

double	sphere_intersection(t_ray ray, t_obj *obj)
{
	double	dist;
	t_vec3	obj_vec;

	obj_vec = vec3_sub(obj->center, ray.origin);
	dist = solve_quadratic(
			vec3_dot(ray.dir, ray.dir),
			-2.0f * vec3_dot(obj_vec, ray.dir),
			vec3_dot(obj_vec, obj_vec) - pow(obj->d / 2.0f, 2)
			);
	return (dist);
}
