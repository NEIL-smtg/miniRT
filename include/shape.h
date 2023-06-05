/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 01:18:20 by suchua            #+#    #+#             */
/*   Updated: 2023/06/02 23:18:03 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

# include "color.h"
# include "matrix.h"

# define LOWCASE	1
# define UPCASE		2

enum	e_type
{
	SPHERE,
	CYLINDER,
	PLANE
};

typedef struct s_obj
{
	int						fix;
	enum e_type				type;
	t_vec					center;
	t_vec					dir;
	double					d;
	double					h;
	t_rgb					rgb;
	struct s_obj			*next;
}	t_obj;

#endif