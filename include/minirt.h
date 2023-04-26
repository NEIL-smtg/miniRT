/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 00:44:26 by suchua            #+#    #+#             */
/*   Updated: 2023/04/27 01:28:52 by suchua           ###   ########.fr       */
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

# define SPHERE		1
# define PLANE		2
# define CYLINDER	3

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	int		x;
	int		y;
}	t_mlx;

////////////////////////////////////////////////////////
/////////////////FUNCTION PROTOTYPE/////////////////////
////////////////////////////////////////////////////////

//init
int			parse_scene(t_scene *scene, char *file);
int			set_ambient(t_scene *scene, char **line);
int			set_cam(t_scene *scene, char **line);
int			set_light(t_scene *scene, char **line);
int			set_cylinder(t_scene *scene, char **line);
int			set_plane(t_scene *scene, char **line);
int			set_sphere(t_scene *scene, char **line);
void		init_mlx(t_mlx *mlx);

//atof
double		ft_atof(char *s);

//objs lst
void		objs_lst_addback(t_objs **objs, t_objs **new);

//error
int			error_msg(char *s);

//validater : error checking
int			valid_vector(t_vector vector);
int			valid_rgb(t_rgb rgb);
int			valid_camera(t_camera cam);
int			valid_light(t_light light, int size);

#endif
