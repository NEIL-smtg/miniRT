/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 00:56:07 by suchua            #+#    #+#             */
/*   Updated: 2023/07/15 01:12:21 by suchua           ###   ########.fr       */
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
