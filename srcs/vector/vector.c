/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 02:04:33 by suchua            #+#    #+#             */
/*   Updated: 2023/05/25 23:15:34 by suchua           ###   ########.fr       */
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
double	get_focal_length(double rad)
{
	return ((double) (WIDTH / 2) / tan(rad / 2));
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

// t_cd	*perspective_projection(t_vec dir, double dot, double fov)
// {
// 	t_cd	*new;
// 	double	focal_length;

// 	new = ft_calloc(1, sizeof(t_cd));
// 	focal_length = get_focal_length(fov);
// 	new->screen_x = (double) (WIDTH / 2) + (focal_length * dir.x / dot);
// 	new->screen_y = (double) (HEIGHT / 2) + (focal_length * dir.y / dot);
// 	return (new);
// }
