/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:37:34 by suchua            #+#    #+#             */
/*   Updated: 2023/05/04 01:46:50 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "shape.h"

typedef struct s_amblight
{
	double		ratio;
	t_rgb		rgb;
}	t_amblight;

typedef struct s_camera
{
	t_pos		pos;
	t_vec		vec;
	double		fov;
}	t_camera;

typedef struct s_light
{
	t_pos		pos;
	double		brightness;
	t_rgb		rgb;
}	t_light;

typedef struct s_scene
{
	t_amblight	amblight;
	t_camera	cam;
	t_light		light;
	t_cy		*cy;
	t_pl		*pl;
	t_sp		*sp;
}	t_scene;

#endif
