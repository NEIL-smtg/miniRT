/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:13:15 by mmuhamad          #+#    #+#             */
/*   Updated: 2023/08/09 13:02:08 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	lglst_addback(t_light **lst, t_light *new)
{
	t_light	*last;

	if (!lst || !*lst)
		*lst = new;
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

static int	valid_light(char **s)
{
	int		size;
	int		flag;

	size = get_2d_arr_size(s);
	flag = 1;
	if (size != 3 && size != 4)
		flag = 0;
	if (!valid_xyz(s[1]))
		flag = 0;
	if (!valid_range(0, 1, ft_atof(s[2])))
		flag = 0;
	if (size == 4 && !valid_rgb(s[3]))
		flag = 0;
	ft_free2d(s);
	return (flag);
}

void	new_light(char *line, t_light *new)
{
	char	**sp;
	char	**xyz;

	sp = rt_split(line);
	xyz = ft_split(sp[1], ',');
	new->pos.x = ft_atof(xyz[0]);
	new->pos.y = ft_atof(xyz[1]);
	new->pos.z = ft_atof(xyz[2]);
	ft_free2d(xyz);
	new->brightness = ft_atof(sp[2]);
	xyz = ft_split(sp[3], ',');
	new->rgb.r = ft_atof(xyz[0]);
	new->rgb.g = ft_atof(xyz[1]);
	new->rgb.b = ft_atof(xyz[2]);
	new->light_intersects = cube_intersection;
	new->next = NULL;
	ft_free2d(xyz);
	ft_free2d(sp);
}

void	new_light_obj(t_light *new, t_obj *lg)
{
	lg->type = LIGHT;
	lg->center.x = new->pos.x;
	lg->center.y = new->pos.y;
	lg->center.z = new->pos.z;
	lg->rgb.r = new->rgb.r;
	lg->rgb.g = new->rgb.g;
	lg->rgb.b = new->rgb.b;
	lg->light = new;
	lg->get_intersects = cube_intersection_obj;
	lg->next = NULL;
}

int	set_light(t_scene *sc, char *line)
{
	t_light	*new;
	t_obj	*lg;

	new = malloc(sizeof(t_light));
	if (!new)
		ft_error("malloc failed on t_light", NULL);
	lg = malloc(sizeof(t_obj));
	lg->light = malloc(sizeof(t_light));
	if (!lg || !lg->light)
		ft_error("malloc failed on obj t_light", NULL);
	new->fix = 0;
	if (*line == 'L')
		new->fix = 1;
	if (!valid_light(rt_split(line)))
	{
		ft_putstr_fd("Error !!\nInvalid arguments for light.", 2);
		return (0);
	}
	new_light(line, new);
	lglst_addback(&(sc->light), new);
	new_light_obj(new, lg);
	objlst_addback(&(sc->obj), lg);
	return (1);
}
