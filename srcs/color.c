/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 00:56:07 by suchua            #+#    #+#             */
/*   Updated: 2023/07/01 16:21:16 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

int	rgb_to_int(t_rgb rgb)
{
	return (rgb.r << 16 | rgb.g << 8 | rgb.b);
}

t_rgb	new_rgb(int r, int g, int b)
{
	t_rgb	new;

	new.r = r;
	new.g = g;
	new.b = b;
	return (new);
}
