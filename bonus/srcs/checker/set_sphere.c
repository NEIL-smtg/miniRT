/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:03:41 by suchua            #+#    #+#             */
/*   Updated: 2023/08/22 17:00:01 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <float.h>

static t_obj	*new_sp(char **s, int type)
{
	t_obj	*new;
	char	**xyz;

	new = ft_calloc(1, sizeof(t_obj));
	if (!new)
		return (NULL);
	new->type = SPHERE;
	new->fix = type - 1;
	xyz = ft_split(s[1], ',');
	new->center.x = ft_atof(xyz[0]);
	new->center.y = ft_atof(xyz[1]);
	new->center.z = ft_atof(xyz[2]);
	ft_free2d(xyz);
	new->d = ft_atof(s[2]);
	xyz = ft_split(s[3], ',');
	new->rgb.r = ft_atof(xyz[0]);
	new->rgb.g = ft_atof(xyz[1]);
	new->rgb.b = ft_atof(xyz[2]);
	new->next = NULL;
	ft_free2d(xyz);
	return (new);
}

int	set_sphere(t_scene *sc, char *line, int type)
{
	char	**s;
	t_obj	*new;

	s = rt_split(line);
	if (get_2d_arr_size(s) != 4 || !valid_xyz(s[1])
		|| !valid_range_str(0, DBL_MAX, s[2], NULL)
		|| !valid_rgb(s[3]))
	{
		ft_free2d(s);
		ft_putstr_fd("Error\nInvalid arguments for sphere!", 2);
		return (0);
	}
	new = new_sp(s, type);
	new->get_intersects = sphere_intersection;
	new->get_uv = texture_sphere_uv;
	new->checkerboard = false;
	new->bump = false;
	objlst_addback(&(sc->obj), new);
	ft_free2d(s);
	return (1);
}
