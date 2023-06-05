/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:44:09 by suchua            #+#    #+#             */
/*   Updated: 2023/06/03 22:45:09 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	objlst_addback(t_obj **lst, t_obj *new)
{
	t_obj	*last;

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

static int	process_line(char *line, t_scene *sc)
{
	if (*line == 'A' || *line == 'a')
		return (set_ambient(&(sc->amblight), line));
	else if (*line == 'L' || *line == 'l')
		return (set_light(&(sc->light), line));
	else if (!ft_strncmp("sp", line, 2))
		return (set_sphere(sc, line, LOWCASE));
	else if (!ft_strncmp("pl", line, 2))
		return (set_plane(sc, line, LOWCASE));
	else if (!ft_strncmp("cy", line, 2))
		return (set_cylinder(sc, line, LOWCASE));
	else if (!ft_strncmp("SP", line, 2))
		return (set_sphere(sc, line, UPCASE));
	else if (!ft_strncmp("PL", line, 2))
		return (set_plane(sc, line, UPCASE));
	else if (!ft_strncmp("CY", line, 2))
		return (set_cylinder(sc, line, UPCASE));
	else if (*line == 'C' || *line == 'c')
		return (set_camera(&(sc->cam), line));
	return (1);
}

int	get_input(char *file, t_scene *sc)
{
	int		fd;
	char	*line;
	int		ret;

	sc->obj = NULL;
	fd = open(file, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ret = process_line(line, sc);
		free(line);
		if (!ret)
			return (0);
	}
	return (1);
}
