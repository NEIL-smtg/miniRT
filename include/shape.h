/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 01:18:20 by suchua            #+#    #+#             */
/*   Updated: 2023/08/07 18:13:48 by mmuhamad         ###   ########.fr       */
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
	double			(*get_intersects)(t_ray ray, struct s_obj *obj);
	void			(*get_uv)(const t_vec3 *point, double *u, \
		double *v, struct s_obj	*obj);
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

#endif