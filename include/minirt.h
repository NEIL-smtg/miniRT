/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 00:44:26 by suchua            #+#    #+#             */
/*   Updated: 2023/08/01 16:45:42 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../Libft/include/libft.h"
# include <mlx.h>
# include <errno.h>
# include <fcntl.h>
# include "quaternion.h"
# include "keys.h"
# include "transformation.h"
# include <stdbool.h>

# define TITLE			"miniRT"
# define HEIGHT			540
# define WIDTH			960

////////////////////////////////////////////////////////
/////////////////FUNCTION PROTOTYPE/////////////////////
////////////////////////////////////////////////////////

//	transformation
void		world_to_camera(t_mat4 inv_view_mat, t_scene *sc);
t_mat4		get_view_matrix(t_camera cam);
t_vec3		convert_to_view_space(t_mat4 view_mat, t_vec3 v);

//	hooks
void		hooks(t_viewport *vp);

//	edit mode
void		ft_edit(t_viewport *vp);
bool		is_edit_key(int keycode, t_viewport *vp);
void		selected_msg(t_obj *selected);

//	render
void		render(t_viewport *vp, t_scene sc);
t_vec3		get_ray_dir(int pixel[2], t_viewport *vp, t_vec3 cam_origin);
double		get_closest_obj(t_ray ray, t_obj *obj, t_obj **closest);
void		fill_color(t_rgb color, t_viewport *vp, int pixel[2]);

//	utils
void		print_scene(t_scene *sc);
double		ft_atof(char *s);
char		**rt_split(char const *s);
void		print_mat4(t_mat4 mat);
void		clean_img(t_viewport *vp);

//valid arg, getting inputs
int			valid_arg(int ac, char **av);
int			get_input(char *file, t_scene *sc);
int			is_fix(t_scene *sc, int *acl, int line);
int			line_error(int line);

//setters
int			set_ambient(t_amblight *al, char *line);
int			set_camera(t_camera *cam, char *line);
int			set_light(t_light *lg, char *line);
int			set_cylinder(t_scene *sc, char *line, int type);
int			set_sphere(t_scene *sc, char *line, int type);
int			set_plane(t_scene *sc, char *line, int type);
int			set_cone(t_scene *sc, char *line, int type);
void		objlst_addback(t_obj **lst, t_obj *new);

//checkers
int			valid_rgb(char *s);
int			valid_range(double from, double to, double nb);
int			valid_xyz(char *s);
int			valid_fov(int fov);
int			valid_vec3(char *s);

//colors
t_rgb		phong_shading(t_scene sc, t_ray ray, t_obj *obj, double t);

#endif
