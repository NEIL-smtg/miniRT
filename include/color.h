/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:32:02 by suchua            #+#    #+#             */
/*   Updated: 2023/07/15 01:12:25 by suchua           ###   ########.fr       */
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

#endif