/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:32:34 by suchua            #+#    #+#             */
/*   Updated: 2023/05/24 03:58:14 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_pl	*new_pl(char **s, int type)
{
	t_pl	*new;
	char	**xyz;

	new = ft_calloc(1, sizeof(t_pl));
	if (!new)
		return (NULL);
	new->fix = type - 1;
	xyz = ft_split(s[1], ',');
	new->pos.x = ft_atof(xyz[0]);
	new->pos.y = ft_atof(xyz[1]);
	new->pos.z = ft_atof(xyz[2]);
	ft_free2d(xyz);
	xyz = ft_split(s[2], ',');
	new->vec.x = ft_atof(xyz[0]);
	new->vec.y = ft_atof(xyz[1]);
	new->vec.z = ft_atof(xyz[2]);
	ft_free2d(xyz);
	xyz = ft_split(s[3], ',');
	new->rgb.r = ft_atoi(xyz[0]);
	new->rgb.g = ft_atoi(xyz[1]);
	new->rgb.b = ft_atoi(xyz[2]);
	new->next = NULL;
	ft_free2d(xyz);
	return (new);
}

static void	pl_lst_add_back(t_pl **pl, t_pl *new)
{
	t_pl	*last;

	if (!new)
		return ;
	if (!pl || !*pl)
		*pl = new;
	else
	{
		last = *pl;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

int	set_plane(t_scene *sc, char *line, int type)
{
	char	**s;

	s = rt_split(line);
	if (get_2d_arr_size(s) != 4 || !valid_xyz(s[1])
		|| !valid_vec3(s[2]) || !valid_rgb(s[3]))
	{
		ft_putendl_fd("Error\nInvalid arguments for plane!", 2);
		ft_free2d(s);
		return (0);
	}
	pl_lst_add_back(&(sc->pl), new_pl(s, type));
	ft_free2d(s);
	return (1);
}
