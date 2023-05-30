/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 00:44:26 by suchua            #+#    #+#             */
/*   Updated: 2023/05/30 18:10:15 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../Libft/include/libft.h"
# include <mlx.h>
# include <math.h>
# include <errno.h>
# include <fcntl.h>
# include "scene.h"

# ifndef M_PI
#  define M_PI	3.14159265358979323846
# endif

# define TITLE	"miniRT"
# define HEIGHT	540
# define WIDTH	960

////////////////////////////////////////////////////////
/////////////////FUNCTION PROTOTYPE/////////////////////
////////////////////////////////////////////////////////

//	utils
void		print_scene(t_scene *sc);
double		ft_atof(char *s);
char		**rt_split(char const *s);

//valid arg, getting inputs
int			valid_arg(int ac, char **av);
int			get_input(char *file, t_scene *sc);

//setters
int			set_ambient(t_amblight *al, char *line);
int			set_camera(t_camera *cam, char *line);
int			set_light(t_light *lg, char *line);
int			set_cylinder(t_scene *sc, char *line, int type);
int			set_sphere(t_scene *sc, char *line, int type);
int			set_plane(t_scene *sc, char *line, int type);

//checkers
int			valid_rgb(char *s);
int			valid_range(double from, double to, double nb);
int			valid_xyz(char *s);
int			valid_fov(int fov);
int			valid_vec3(char *s);

//vector
t_vec		new_vec(double x, double y, double z);
double		dot_product(t_vec v1, t_vec v2);
t_vec		normalize(t_vec vec);
double		get_focal_length(double rad, double width);
t_vec		get_raydir(double u, double v, t_viewport vp);
void		print_vector(t_vec v, char *name);
double		get_radian(int angle);
t_vec		vec_mul(double scalar, t_vec v);
t_vec		cross_product(t_vec a, t_vec b);


#endif
