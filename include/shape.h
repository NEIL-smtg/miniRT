/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 01:18:20 by suchua            #+#    #+#             */
/*   Updated: 2023/08/18 01:50:17 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

# include "color.h"
# include "matrix.h"
# include <stdbool.h>

# define LOWCASE	1
# define UPCASE		2

# ifndef EPS
#  define EPS 1e-6
# endif

# define PL_DIFFUSE_TERM 0.25
# define PL_SPECULAR_TERM 5.0

typedef struct s_tuv
{
	t_vec3	ci;
	double	u;
	double	v;
	double	r;
	double	h;
	int		t_width;
	int		t_height;
}	t_tuv;

typedef struct s_ray
{
	t_vec3	dir;
	t_vec3	origin;
}	t_ray;

enum	e_type
{
	SPHERE,
	CYLINDER,
	PLANE,
	CONE ,
	LIGHT
};

typedef struct s_obj
{
	bool			edit_h;
	bool			edit_d;
	bool			checkerboard;
	bool			bump;
	int				fix;
	int				id;
	enum e_type		type;
	t_vec3			center;
	t_vec3			dir;
	double			d;
	double			h;
	double			cone_angle;
	t_rgb			rgb;
	t_rgb			tmp_color;
	struct s_obj	*next;
	struct s_light	*light;
	double			(*get_intersects)(t_ray ray, struct s_obj *obj);
	void			(*get_uv)(t_tuv *g);
}	t_obj;

// quadratic
double	solve_quadratic(double a, double b, double c);

// to calculate t which refer to distance of intersection
// between the object and the camera
double	sphere_intersection(t_ray ray, t_obj *obj);
double	plane_intersection(t_ray ray, t_obj *obj);
double	cylinder_intersection(t_ray ray, t_obj *obj);
double	cone_intersection(t_ray ray, t_obj *obj);

//	getting projection
t_vec3	get_projection(t_vec3 v, t_vec3 obj_dir);

//	uv texture mapping
void	texture_sphere_uv(t_tuv *g);
void	texture_plane_uv(t_tuv *g);
void	texture_cy_uv(t_tuv *g);
void	texture_cone_uv(t_tuv *g);

#endif