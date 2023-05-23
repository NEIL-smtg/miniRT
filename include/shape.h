/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 01:18:20 by suchua            #+#    #+#             */
/*   Updated: 2023/05/23 17:53:04 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

# include "color.h"

# define LOWCASE	1
# define UPCASE		2

typedef struct s_pos
{
	double	x;
	double	y;
	double	z;
}	t_pos;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_cy
{
	int			fix;
	t_pos		center;
	t_vec		vec;
	double		d;
	double		h;
	t_rgb		rgb;
	struct s_cy	*next;
}	t_cy;

typedef struct s_pl
{
	int			fix;
	t_pos		pos;
	t_vec		vec;
	t_rgb		rgb;
	struct s_pl	*next;
}	t_pl;

typedef struct s_sp
{
	int			fix;
	t_pos		center;
	double		d;
	t_rgb		rgb;
	struct s_sp	*next;
}	t_sp;

#endif