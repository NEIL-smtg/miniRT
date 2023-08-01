/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:06:55 by suchua            #+#    #+#             */
/*   Updated: 2023/08/01 18:04:06 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"

// a   = D|D - (1+k*k)*(D|V)^2
// b/2 = D|X - (1+k*k)*(D|V)*(X|V)
// c   = X|X - (1+k*k)*(X|V)^2
double	cone_intersection(t_ray ray, t_obj *obj)
{
	t_vec3	oc;
	double	t;
	double	k;

	obj->apex = vec3_add(obj->center, vec3_mul(obj->h, obj->dir));
	oc = vec3_sub(obj->apex, ray.dir);
	k = tan(get_radian(obj->cone_angle / 2));
	t = solve_quadratic(
		vec3_dot(ray.dir, ray.dir) - (1 + k * k) * pow(vec3_dot(ray.dir, obj->dir), 2),
		-2 * (vec3_dot(ray.dir, oc) - (1 + k * k) * vec3_dot(ray.dir, obj->dir) * vec3_dot(oc, obj->dir)),
		vec3_dot(oc, oc) - (1 + k * k) * pow(vec3_dot(oc, obj->dir), 2)
	);
	return (t);
}
