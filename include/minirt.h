/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 00:44:26 by suchua            #+#    #+#             */
/*   Updated: 2023/07/24 00:07:41 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../Libft/include/libft.h"
# include <mlx.h>
# include <errno.h>
# include <fcntl.h>
# include "scene.h"
# include "quaternion.h"

# define TITLE	"miniRT"
# define HEIGHT	540
# define WIDTH	960

////////////////////////////////////////////////////////
/////////////////FUNCTION PROTOTYPE/////////////////////
////////////////////////////////////////////////////////

//	transformation
void		world_to_camera(t_mat4 inv_view_mat, t_scene *sc);
t_mat4		get_view_matrix(t_camera cam);
void		rotation_transformation(t_mat4 inv_view_mat, t_scene *sc);
t_vec3		convert_to_view_space(t_mat4 view_mat, t_vec3 v);

//	render
void		render(t_viewport *vp, t_scene sc);

//	utils
void		print_scene(t_scene *sc);
double		ft_atof(char *s);
char		**rt_split(char const *s);
double		get_focal_length(double rad, double width);
void		print_mat4(t_mat4 mat);
void		clean_img(t_viewport *vp);

//valid arg, getting inputs
int			valid_arg(int ac, char **av);
int			get_input(char *file, t_scene *sc);

//setters
int			set_ambient(t_amblight *al, char *line);
int			set_camera(t_camera *cam, char *line);
int			set_light(t_light *lg, char *line);
void		objlst_addback(t_obj **lst, t_obj *new);
int			set_cylinder(t_scene *sc, char *line, int type);
int			set_sphere(t_scene *sc, char *line, int type);
int			set_plane(t_scene *sc, char *line, int type);

//checkers
int			valid_rgb(char *s);
int			valid_range(double from, double to, double nb);
int			valid_xyz(char *s);
int			valid_fov(int fov);
int			valid_vec3(char *s);

// transformation
void		ft_forward(t_viewport *vp);
void		ft_backward(t_viewport *vp);
void		ft_right(t_viewport *vp);
void		ft_left(t_viewport *vp);
void		ft_up(t_viewport *vp);
void		ft_down(t_viewport *vp);
void		ft_panning_right(t_viewport *vp);
void		ft_panning_left(t_viewport *vp);

//colors
t_rgb		phong_shading(t_scene sc, t_ray ray, t_obj *obj, double t);

#endif
