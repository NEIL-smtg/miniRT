/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_uv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neilsundae <suchua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:29:45 by mmuhamad          #+#    #+#             */
/*   Updated: 2023/09/08 02:36:26 by neilsundae       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Map the checkerboard pattern to UV coordinates
void	get_sphere_uv(const t_vec3 *point, double *u, double *v, t_obj *obj)
{
	double	normalized_x;
	double	normalized_y;

	normalized_x = (point->x + obj->d / 2.0) / obj->d;
	normalized_y = (point->y + obj->d / 2.0) / obj->d;
	*u = 1.0 - normalized_x;
	*v = 1.0 - normalized_y;
}

void	get_plane_uv(const t_vec3 *point, double *u, double *v)
{
	*u = remainder(point->x, 1.0f) + 0.4;
	*v = remainder(point->z, 1.0f) + 0.4;
}

void	get_cylinder_uv(const t_vec3 *point, double *u, double *v, t_obj *obj)
{
	double	normalized_x;
	double	normalized_y;

	normalized_x = (point->x + obj->d / 2.0) / obj->d;
	normalized_y = (point->y + obj->d / 2.0) / obj->d;
	*u = 1.0 - normalized_x;
	*v = 1.0 - normalized_y;
}
