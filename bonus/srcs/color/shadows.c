/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 23:40:31 by suchua            #+#    #+#             */
/*   Updated: 2023/08/21 19:56:59 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//	RMB TO NORMALIZE RAY DIRECTIONNNNNNNNNN !!!!!!!
bool	in_shadows(t_scene sc, t_vec3 inter, t_obj *obj, double diffuse)
{
	t_obj	*closest;
	t_ray	ray;
	double	t;

	if (diffuse == 0.0)
		return (false);
	closest = NULL;
	ray.dir = normalize(vec3_sub(sc.light->pos, inter));
	ray.origin = vec3_add(inter, vec3_mul(EPS, ray.dir));
	t = get_closest_obj(ray, sc.obj, &closest, false);
	while (closest && closest == obj)
	{
		closest = NULL;
		ray.origin = vec3_add(inter, vec3_mul(t, ray.dir));
		t += get_closest_obj(ray, sc.obj, &closest, false) + EPS;
	}
	if (t == INFINITY)
		return (false);
	if (t >= vec3_len(vec3_sub(sc.light->pos, inter)) - EPS)
		return (false);
	return (closest != NULL);
}
