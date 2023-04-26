/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:37:34 by suchua            #+#    #+#             */
/*   Updated: 2023/04/27 01:10:09 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "color.h"

typedef struct s_amblight
{
	double	ratio;
	t_rgb	rgb;
}	t_amblight;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_pos
{
	double	x;
	double	y;
	double	z;
}	t_pos;

typedef struct s_camera
{
	t_pos		pos;
	t_vector	vector;
	int			fov;
}	t_camera;

typedef struct s_light
{
	t_pos	pos;
	double	brightness;
	t_rgb	rgb;;
}	t_light;

typedef struct s_objs
{
	//sp
	int				type;
	t_pos			pos;
	double			diameter;
	t_rgb			rgb;
	//pl
	t_vector		vector;
	//cy
	double			height;
	struct s_objs	*next;
}	t_objs;

typedef struct s_scene
{
	t_amblight	amblight;
	t_camera	cam;
	t_light		light;
	t_objs		*objs;
}	t_scene;

#endif
