/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:37:34 by suchua            #+#    #+#             */
/*   Updated: 2023/06/02 23:19:31 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "shape.h"
# include "matrix.h"

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
	t_obj		*obj;
}	t_scene;

typedef struct s_img
{
	void	*img_ptr;
	char	*data_addr;
	int		bpp;
	int		line_size;
	int		endian;
}	t_img;

typedef struct s_viewport
{
	double	w;
	double	h;
	double	focal;
	double	aspect_ratio;
	void	*mlx;
	void	*win;
	t_mat	transform;
	t_vec	origin;
	t_img	*img;
}	t_viewport;

#endif
