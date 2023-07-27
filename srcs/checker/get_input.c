/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:44:09 by suchua            #+#    #+#             */
/*   Updated: 2023/07/27 18:03:04 by mmuhamad         ###   ########.fr       */
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

static int	line_error(int line)
{
	ft_putstr_fd(" line : [", 2);
	ft_putnbr_fd(line, 2);
	ft_putendl_fd("]", 2);
	return (0);
}

void	set_id(t_scene *sc)
{
	int		id;
	t_obj	*head;

	id = 0;
	head = sc->obj;
	while (sc->obj->next)
	{
		sc->obj->id = id;
		id++;
		sc->obj = sc->obj->next;
	}
	sc->obj = head;
}

int	get_input(char *file, t_scene *sc)
{
	int		fd;
	char	*line;
	int		ret;
	int		i;
	int		id;

	id = 0;
	sc->obj = NULL;
	fd = open(file, O_RDONLY);
	i = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ret = process_line(line, sc);
		free(line);
		++i;
		if (!ret)
			return (line_error(i));
	}
	set_id(sc);
	return (1);
}
