/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 01:18:20 by suchua            #+#    #+#             */
/*   Updated: 2023/07/04 01:30:20 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

# include "color.h"
# include "matrix.h"

# define LOWCASE	1
# define UPCASE		2

typedef struct s_ray
{
	t_vec3	dir;
	t_vec3	origin;
}	t_ray;

enum	e_type
{
	SPHERE,
	CYLINDER,
	PLANE
};

typedef struct s_obj
{
	int				fix;
	enum e_type		type;
	t_vec3			center;
	t_vec3			dir;
	double			d;
	double			h;
	t_rgb			rgb;
	struct s_obj	*next;
	double			(*get_intersects)(t_ray ray, struct s_obj *obj);
}	t_obj;

// quadratic
double	solve_quadratic(double a, double b, double c);

// to calculate t which refer to distance of intersection
// between the object and the camera
double	sphere_intersection(t_ray ray, t_obj *obj);
double	plane_intersection(t_ray ray, t_obj *obj);
double	cylinder_intersection(t_ray ray, t_obj *obj);

#endif