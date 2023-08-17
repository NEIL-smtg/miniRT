/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:37:34 by suchua            #+#    #+#             */
/*   Updated: 2023/08/16 12:12:03 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "shape.h"
# include "color.h"
# include "matrix.h"
# include <pthread.h>
# include <stdbool.h>

typedef struct s_amblight
{
	int			fix;
	double		ratio;
	t_rgb		rgb;
}	t_amblight;

typedef struct s_camera
{
	int			fix;
	t_vec3		pos;
	t_vec3		dir;
	double		fov;
}	t_camera;

typedef struct s_light
{
	int				fix;
	t_vec3			pos;
	double			brightness;
	t_rgb			rgb;
	double			(*light_intersects)(t_ray ray, struct s_light *light);
	struct s_light	*next;
}	t_light;

typedef struct s_scene
{
	t_amblight	amblight;
	t_camera	cam;
	t_obj		*obj;
	t_light		*light;
}	t_scene;

typedef struct s_img
{
	void	*ptr;
	char	*data_addr;
	int		bpp;
	int		line_size;
	int		endian;
	int		width;
	int		height;
	double	**bump_map;
}	t_img;

typedef struct s_viewport
{
	double			w;
	double			h;
	double			focal;
	double			aspect_ratio;
	void			*mlx;
	void			*win;
	bool			edit;
	bool			checkerboard;
	t_img			img;
	t_img			texture;
	t_mat4			view_mat;
	t_mat4			inv_view_mat;
	t_scene			*scene;
	t_obj			*selected;
	int				pixel[2];
	pthread_mutex_t	render;
}	t_viewport;

void	edit_property(int key, t_obj *selected);
void	selected_msg(t_obj *selected);

double	cube_intersection(t_ray ray, t_light *obj);
double	cube_intersection_obj(t_ray ray, t_obj *obj);

#endif
