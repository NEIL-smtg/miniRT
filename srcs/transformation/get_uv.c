/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_uv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:29:45 by mmuhamad          #+#    #+#             */
/*   Updated: 2023/08/02 15:35:01 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Map the checkerboard pattern to UV coordinates
void	get_sphere_uv(const t_vec3 *point, double *u, double *v, t_obj *obj)
{
	double	normalized_x;
	double	normalized_y;
	double	normalized_z;

	normalized_x = (point->x + obj->d / 2.0) / obj->d;
	normalized_y = (point->y + obj->d / 2.0) / obj->d;
	normalized_z = (point->z + obj->d / 2.0) / obj->d;
	*u = 1.0 - normalized_x;
	*v = 1.0 - normalized_y;
}

void	get_plane_uv(const t_vec3 *point, double *u, double *v, t_obj *obj)
{
	*u = remainder(point->x, 1.0f) + 0.4;
	*v = remainder(point->z, 1.0f) + 0.4;
}

void	get_cylinder_uv(const t_vec3 *point, double *u, double *v, t_obj *obj)
{
	double	normalized_x;
	double	normalized_y;
	double	normalized_z;

	normalized_x = (point->x + obj->d / 2.0) / obj->d;
	normalized_y = (point->y + obj->d / 2.0) / obj->d;
	normalized_z = (point->z + obj->d / 2.0) / obj->d;
	*u = 1.0 - normalized_x;
	*v = 1.0 - normalized_y;
}
