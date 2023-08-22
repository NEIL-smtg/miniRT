/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 21:33:17 by suchua            #+#    #+#             */
/*   Updated: 2023/08/22 13:43:50 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../../Libft/include/libft.h"
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
# define SAMPLE_STEP	4.0

# ifndef THREAD_NUM
#  define THREAD_NUM 8
# endif

//	render struct
typedef struct s_th
{
	t_viewport	*vp;
	int			start_y;
	int			end_y;
}	t_th;

typedef struct s_render
{
	pthread_t	th[THREAD_NUM];
	t_th		data[THREAD_NUM];
	int			lines_per_thread;
	int			remaining_lines;
}	t_render;

typedef struct s_vec2
{
	double	u;
	double	v;
}	t_vec2;

typedef struct s_stuff
{
	t_vec3	inter;
	double	t;
	t_vec3	surface_normal;
	double	diffuse;
	t_rgb	specular;
	t_rgb	color;
	t_rgb	amb;
	t_scene	sc;
}	t_stuff;

////////////////////////////////////////////////////////
/////////////////FUNCTION PROTOTYPE/////////////////////
////////////////////////////////////////////////////////

//	init
void		init_texture(char *xpm, t_img *texture, void *mlx);

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
void		render(t_viewport *vp);
void		*routine(void *arg);
void		anti_aliasing(int pixel[2], t_viewport *vp, int *x);
t_vec3		get_ray_dir(int pixel[2], t_viewport *vp, t_vec3 cam_origin);
double		get_closest_obj(t_ray ray, t_obj *obj, t_obj **closest, bool edit);
void		fill_color(t_rgb color, t_viewport *vp, int pixel[2]);

//	utils
void		print_scene(t_scene *sc);
double		ft_atof(char *s);
char		**rt_split(char const *s);
void		print_mat4(t_mat4 mat);
void		clean_img(t_viewport *vp);
double		nb_clamp(double n, double min, double max);
void		ft_error(char *s1, char *s2);

//valid arg, getting inputs
int			valid_arg(int ac, char **av);
int			get_input(char *file, t_scene *sc);
int			is_fix(t_scene *sc, int *acl, int line);
int			line_error(int line);

//setters
int			set_ambient(t_amblight *al, char *line);
int			set_camera(t_camera *cam, char *line);
int			set_light(t_scene *sc, char *line);
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

// printing
void		print_obj(t_obj *tmp);

//phong
t_vec3		reflect(t_vec3 incident, t_vec3 surface_normal);
t_rgb		get_specular_light(t_scene sc, t_vec3 surface_normal, \
		t_vec3 inter, t_obj *obj);
double		get_diffuse_color(t_light *light, t_vec3 inter, \
		t_vec3 surface_normal);
t_rgb		get_ambient_color(t_amblight amb, t_rgb color);
bool		in_shadows(t_scene sc, t_vec3 inter, t_obj *obj, double diffuse);

//	getting surface normal for rendering the correct color
t_vec3		get_surface_normal(t_ray ray, t_obj *obj, double t, t_img texture);

//	bump normal
t_vec3		get_bump_effect_normal(t_obj *obj, t_vec3 inter, t_vec3 n, \
			t_img texture);

//colors
t_rgb		phong_shading(t_viewport *vp, t_ray ray, t_obj *obj, double t);
t_rgb		checkerboard(t_viewport *vp, t_ray ray, t_obj *obj, double t);
t_rgb		checkerboard_extend(t_stuff	*stuff, t_obj *obj, t_tuv *g);
t_rgb		edit_mode(t_viewport *vp, t_ray ray, t_obj *obj, double t);

#endif
