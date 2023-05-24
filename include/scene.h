/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:37:34 by suchua            #+#    #+#             */
/*   Updated: 2023/05/25 00:08:47 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "shape.h"

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	int		w;
	int		h;
}	t_mlx;

typedef struct s_amblight
{
	int			fix;
	double		ratio;
	t_rgb		rgb;
}	t_amblight;

typedef struct s_camera
{
	int			fix;
	t_vec		pos;
	t_vec		vec;
	double		fov;
}	t_camera;

typedef struct s_light
{
	int			fix;
	t_vec		pos;
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
