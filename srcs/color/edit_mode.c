/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:26:46 by mmuhamad          #+#    #+#             */
/*   Updated: 2023/08/07 18:08:40 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	get_closest_light(t_ray ray, t_viewport *vp, t_light **closest, double t)
{
	t_light	*light;
	double	dist[2];

	light = vp->scene->light;
	dist[0] = INFINITY;
	while (light)
	{
		dist[1] = light->light_intersects(ray, light);
		if (dist[1] != INFINITY && dist[1] < dist[0])
		{
			*closest = light;
			dist[0] = dist[1];
		}
		light = light->next;
	}
	if (dist[0] < t)
	{
		closest = NULL;
	}
	return (t);
}

t_rgb	edit_mode(t_viewport *vp, t_ray ray, t_obj *obj, double t)
{
	t_light	*lg;
	t_light	*closest;
	double	dist[2];

	lg = vp->scene->light;
	dist[0] = INFINITY;
	while (lg)
	{
		dist[1] = lg->light_intersects(ray, lg);
		if (dist[1] != INFINITY && dist[1] < dist[0])
		{
			closest = lg;
			dist[0] = dist[1];
		}
		lg = lg->next;
	}
	if (dist[0] < t)
	{
		return (closest->rgb);
	}
	if (obj == NULL)
	{
		return (new_rgb(0, 0, 0));
	}
	return (obj->rgb);
}
