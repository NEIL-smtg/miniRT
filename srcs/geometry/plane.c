/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 16:23:05 by suchua            #+#    #+#             */
/*   Updated: 2023/07/01 22:10:07 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"

double	plane_intersection(t_ray ray, t_obj *obj)
{
	t_vec3	origin_center;
	double	t;
	double	divisor;

	origin_center = vec3_sub(obj->center, ray.origin);
	divisor = vec3_dot(ray.dir, obj->dir);
	if (divisor == 0.0f)
		return (INFINITY);
	t = -vec3_dot(origin_center, obj->dir) / divisor;
	if (t <= 0.0f)
		return (INFINITY);
	return (t);
}
