/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 23:44:40 by suchua            #+#    #+#             */
/*   Updated: 2023/08/08 23:57:12 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

t_rgb	rgb_add(t_rgb c1, t_rgb c2)
{
	t_rgb	new;

	new.r = c1.r + c2.r;
	new.g = c1.g + c2.g;
	new.b = c1.b + c2.b;
	return (new);
}

t_rgb	rgb_add_3(t_rgb a, t_rgb b, t_rgb c)
{
	t_rgb	new;

	new = rgb_add(a, b);
	new = rgb_add(new, c);
	return (new);
}
