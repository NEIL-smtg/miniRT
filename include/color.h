/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:32:02 by suchua            #+#    #+#             */
/*   Updated: 2023/07/27 23:10:36 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct s_rgb
{
	double	r;
	double	g;
	double	b;
}	t_rgb;

// int		rgb_to_int(t_rgb rgb);
t_rgb	new_rgb(double r, double g, double b);
t_rgb	clamp(t_rgb color, double from, double to);
t_rgb	rgb_mul(t_rgb c1, t_rgb c2);
t_rgb	rgb_add(t_rgb c1, t_rgb c2);
t_rgb	rgb_scale(double scale, t_rgb color);
t_rgb	get_selected_color(t_rgb c);

#endif