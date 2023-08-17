/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 00:56:07 by suchua            #+#    #+#             */
/*   Updated: 2023/08/08 23:57:10 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

// int	rgb_to_int(t_rgb rgb)
// {
// 	return (rgb.r << 16 | rgb.g << 8 | rgb.b);
// }

t_rgb	new_rgb(double r, double g, double b)
{
	t_rgb	new;

	new.r = r;
	new.g = g;
	new.b = b;
	return (new);
}

t_rgb	clamp(t_rgb color, double from, double to)
{
	if (color.r < from)
		color.r = from;
	else if (color.r > to)
		color.r = to;
	if (color.g < from)
		color.g = from;
	else if (color.g > to)
		color.g = to;
	if (color.b < from)
		color.b = from;
	else if (color.b > to)
		color.b = to;
	return (color);
}

t_rgb	rgb_mul(t_rgb c1, t_rgb c2)
{
	t_rgb	new;

	new.r = c1.r * c2.r;
	new.g = c1.g * c2.g;
	new.b = c1.b * c2.b;
	return (new);
}

t_rgb	rgb_scale(double scale, t_rgb color)
{
	color.r *= scale;
	color.g *= scale;
	color.b *= scale;
	return (color);
}
