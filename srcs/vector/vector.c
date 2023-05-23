/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 02:04:33 by suchua            #+#    #+#             */
/*   Updated: 2023/05/24 02:33:20 by suchua           ###   ########.fr       */
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
	return ((width / 2) / tan(rad / 2));
}

t_vec	normalize(t_vec vec)
{
	double	sp_dir_len;

	sp_dir_len = sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
	return (new_vec(
			vec.x / sp_dir_len,
			vec.y / sp_dir_len,
			vec.z / sp_dir_len
		));
}

//	p_factor = projection factor
t_cd	perspective_projection(t_vec dir, double dot, double width,
		double fov)
{
	t_cd	new;
	double	focal;

	new.screen_x = (double) WIDTH / 2;
	new.screen_y = (double) HEIGHT / 2;
	if (dot == 0.0f)
		return (new);
	focal = get_focal_length(fov, width);
	new.screen_x = (width / 2) + (focal * dir.x / dot);
	new.screen_y = (width / 2) + (focal * dir.y / dot);
	return (new);
}
