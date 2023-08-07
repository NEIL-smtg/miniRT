/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:32:34 by suchua            #+#    #+#             */
/*   Updated: 2023/08/08 00:27:51 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_obj	*new_pl(char **s, int type)
{
	t_obj	*new;
	char	**xyz;

	new = ft_calloc(1, sizeof(t_obj));
	if (!new)
		return (NULL);
	new->type = PLANE;
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
	xyz = ft_split(s[3], ',');
	new->rgb.r = ft_atof(xyz[0]);
	new->rgb.g = ft_atof(xyz[1]);
	new->rgb.b = ft_atof(xyz[2]);
	new->next = NULL;
	ft_free2d(xyz);
	return (new);
}

int	set_plane(t_scene *sc, char *line, int type)
{
	char	**s;
	t_obj	*new;

	s = rt_split(line);
	if (get_2d_arr_size(s) != 4 || !valid_xyz(s[1])
		|| !valid_vec3(s[2]) || !valid_rgb(s[3]))
	{
		ft_putstr_fd("Error\nInvalid arguments for plane!", 2);
		ft_free2d(s);
		return (0);
	}
	new = new_pl(s, type);
	new->get_intersects = plane_intersection;
	new->get_uv = texture_plane_uv;
	new->checkerboard = false;
	new->bump = false;
	objlst_addback(&(sc->obj), new);
	ft_free2d(s);
	return (1);
}
