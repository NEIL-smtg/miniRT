/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:32:02 by suchua            #+#    #+#             */
/*   Updated: 2023/04/27 04:30:41 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

int		rgb_to_int(t_rgb rgb);

# endif
