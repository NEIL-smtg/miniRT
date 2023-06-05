/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:03:41 by suchua            #+#    #+#             */
/*   Updated: 2023/06/02 23:26:48 by suchua           ###   ########.fr       */
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
	new->rgb.r = ft_atoi(xyz[0]);
	new->rgb.g = ft_atoi(xyz[1]);
	new->rgb.b = ft_atoi(xyz[2]);
	new->next = NULL;
	ft_free2d(xyz);
	return (new);
}

int	set_sphere(t_scene *sc, char *line, int type)
{
	char	**s;

	s = rt_split(line);
	if (get_2d_arr_size(s) != 4 || !valid_xyz(s[1])
		|| !valid_range(0, DBL_MAX, ft_atof(s[2]))
		|| !valid_rgb(s[3]))
	{
		ft_free2d(s);
		ft_putendl_fd("Error\nInvalid arguments for sphere!", 2);
		return (0);
	}
	objlst_addback(&(sc->obj), new_sp(s, type));
	ft_free2d(s);
	return (1);
}
