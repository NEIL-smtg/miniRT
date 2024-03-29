/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 23:06:34 by suchua            #+#    #+#             */
/*   Updated: 2023/08/15 03:27:21 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# ifndef M_PI
#  define M_PI	3.14159265358979323846
# endif

# include <math.h>

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_vec4
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_vec4;

//vector
t_vec3		new_vec3(double x, double y, double z);
t_vec4		new_vec4(double x, double y, double z, double w);
void		print_vec3(t_vec3 v, char *name);
double		get_radian(int angle);

// convertion
t_vec3		convert_to_3d(t_vec4 v);
t_vec4		convert_to_4d(t_vec3 v);

//calculation
t_vec3		normalize(t_vec3 vec);
double		vec3_len(t_vec3 v);
t_vec3		vec3_mul(double scalar, t_vec3 v);
double		vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3		vec3_cross(t_vec3 a, t_vec3 b);
t_vec3		vec3_add(t_vec3 a, t_vec3 b);
t_vec3		vec3_sub(t_vec3 a, t_vec3 b);

double		vec4_dot(t_vec4 v1, t_vec4 v2);
double		vec4_len(t_vec4 v);
t_vec4		vec4_normalize(t_vec4 vec);
t_vec4		vec4_mul(double scalar, t_vec4 v);

#endif
