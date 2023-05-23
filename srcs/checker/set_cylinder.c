/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:39:16 by suchua            #+#    #+#             */
/*   Updated: 2023/05/23 18:55:05 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <float.h>

static t_cy	*init_new_part1(char **s, int type)
{
	t_cy	*new;
	char	**xyz;

	new = ft_calloc(1, sizeof(t_cy));
	if (!new)
		return (NULL);
	new->fix = type - 1;
	xyz = ft_split(s[1], ',');
	new->center.x = ft_atof(xyz[0]);
	new->center.y = ft_atof(xyz[1]);
	new->center.z = ft_atof(xyz[2]);
	ft_free2d(xyz);
	xyz = ft_split(s[2], ',');
	new->vec.x = ft_atof(xyz[0]);
	new->vec.y = ft_atof(xyz[1]);
	new->vec.z = ft_atof(xyz[2]);
	ft_free2d(xyz);
	xyz = ft_split(s[5], ',');
	new->rgb.r = ft_atoi(xyz[0]);
	new->rgb.g = ft_atoi(xyz[1]);
	new->rgb.b = ft_atoi(xyz[2]);
	new->next = NULL;
	ft_free2d(xyz);
	return (new);
}

static void	cy_lst_add_back(t_cy **cy, t_cy *new)
{
	t_cy	*last;

	if (!new)
		return ;
	if (!cy || !*cy)
		*cy = new;
	else
	{
		last = *cy;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

int	set_cylinder(t_scene *sc, char *line, int type)
{
	char	**s;
	t_cy	*new;

	s = ft_split(line, 32);
	if (get_2d_arr_size(s) != 6 || !valid_xyz(s[1])
		|| !valid_vec3(s[2])
		|| !valid_range(0, DBL_MAX, ft_atof(s[3]))
		|| !valid_range(0, DBL_MAX, ft_atof(s[4]))
		|| !valid_rgb(s[5]))
	{
		ft_free2d(s);
		ft_putendl_fd("Error\nInvalid arguments for cylinder!", 2);
		return (0);
	}
	new = init_new_part1(s, type);
	new->d = ft_atof(s[3]);
	new->h = ft_atof(s[4]);
	cy_lst_add_back(&(sc->cy), new);
	ft_free2d(s);
	return (1);
}
