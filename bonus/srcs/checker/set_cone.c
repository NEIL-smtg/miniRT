/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:17:23 by suchua            #+#    #+#             */
/*   Updated: 2023/08/08 00:27:59 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <float.h>

//		 center    normal   r  h  angle     color
//	cy	-8,3,13  -1,0,-0.2  3  1   30     150,88,200
static t_obj	*init_new_part1(char **s, int type)
{
	t_obj	*new;
	char	**xyz;

	new = ft_calloc(1, sizeof(t_obj));
	if (!new)
		return (NULL);
	new->fix = type - 1;
	xyz = ft_split(s[1], ',');
	new->center.x = ft_atof(xyz[0]);
	new->center.y = ft_atof(xyz[1]);
	new->center.z = ft_atof(xyz[2]);
	ft_free2d(xyz);
	xyz = ft_split(s[2], ',');
	new->dir.x = ft_atof(xyz[0]);
	new->dir.y = ft_atof(xyz[1]);
	new->dir.z = ft_atof(xyz[2]);
	ft_free2d(xyz);
	xyz = ft_split(s[5], ',');
	new->rgb.r = ft_atof(xyz[0]);
	new->rgb.g = ft_atof(xyz[1]);
	new->rgb.b = ft_atof(xyz[2]);
	new->next = NULL;
	ft_free2d(xyz);
	return (new);
}

static void	init_part2(t_obj **new, char **s)
{
	(*new)->checkerboard = false;
	(*new)->bump = false;
	(*new)->type = CONE;
	(*new)->get_intersects = cone_intersection;
	(*new)->get_uv = texture_cone_uv;
	(*new)->d = ft_atof(s[3]);
	(*new)->h = ft_atof(s[4]);
	(*new)->cone_angle = atan((*new)->d / 2.0 / (*new)->h);
}

//		 center    normal   r  h  angle     color
//	cy	-8,3,13  -1,0,-0.2  3  1   30     150,88,200
int	set_cone(t_scene *sc, char *line, int type)
{
	char	**s;
	t_obj	*new;

	s = rt_split(line);
	if (get_2d_arr_size(s) != 6 || !valid_xyz(s[1])
		|| !valid_vec3(s[2])
		|| !valid_range(0, DBL_MAX, ft_atof(s[3]))
		|| !valid_range(0, DBL_MAX, ft_atof(s[4]))
		|| !valid_range(0, 90, atan(ft_atof(s[3]) / ft_atof(s[4])))
		|| !valid_rgb(s[5]))
	{
		ft_free2d(s);
		ft_putstr_fd("Error\nInvalid arguments for cone!", 2);
		return (0);
	}
	new = init_new_part1(s, type);
	init_part2(&new, s);
	objlst_addback(&(sc->obj), new);
	ft_free2d(s);
	return (1);
}
