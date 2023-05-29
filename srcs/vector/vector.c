/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 02:04:33 by suchua            #+#    #+#             */
/*   Updated: 2023/05/28 17:00:25 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	new_vec(double x, double y, double z)
{
	t_vec	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

double	dot_product(t_vec v1, t_vec v2)
{
	double	x;
	double	y;
	double	z;

	x = v1.x * v2.x;
	y = v1.y * v2.y;
	z = v1.z * v2.z;
	return (x + y + z);
}

//	calculate focal length
double	get_focal_length(double rad, double width)
{
	return ((WIDTH / 2) / tan(rad / 2));
}

t_vec	normalize(t_vec vec)
{
	double	dir_len;

	dir_len = sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
	return (new_vec(
			vec.x / dir_len,
			vec.y / dir_len,
			vec.z / dir_len
		));
}

t_vec	get_raydir(double u, double v, t_viewport vp)
{
	t_vec	corner;
	t_vec	hor;
	t_vec	ver;
	t_vec	origin;

	corner = vp.corner;
	hor = vp.horizontal;
	ver = vp.vertical;
	origin = vp.origin;
	return (new_vec
		(
			corner.x + u * hor.x + v * ver.x - origin.x,
			corner.y + u * hor.y + v * ver.y - origin.y,
			corner.z + u * hor.z + v * ver.z - origin.z
		));
}
