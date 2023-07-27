/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:44:09 by suchua            #+#    #+#             */
/*   Updated: 2023/07/27 21:33:25 by suchua           ###   ########.fr       */
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

int	line_error(int line)
{
	ft_putstr_fd(" line : [", 2);
	ft_putnbr_fd(line, 2);
	ft_putendl_fd("]", 2);
	return (0);
}

static int	set_acl(char *line, int *acl, t_scene *sc)
{
	if (*line == 'A' || *line == 'a')
		acl[0]++;
	if (sc->amblight.fix && acl[0] > 1)
		return (0);
	if (*line == 'L' || *line == 'l')
		acl[2]++;
	if (sc->light.fix && acl[2] > 1)
		return (0);
	if (!ft_strncmp("CY", line, 2) || !ft_strncmp("cy", line, 2))
		return (1);
	if (*line == 'C' || *line == 'c')
		acl[1]++;
	if (sc->cam.fix && acl[1] > 1)
		return (0);
	return (1);
}

int	get_input(char *file, t_scene *sc)
{
	int		fd;
	char	*line;
	int		ret;
	int		i;
	int		*acl;

	sc->obj = NULL;
	fd = open(file, O_RDONLY);
	i = 1;
	acl = ft_calloc(3, sizeof(int));
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!set_acl(line, acl, sc))
			break ;
		ret = process_line(line, sc);
		free(line);
		++i;
		if (!ret)
			return (line_error(i));
	}
	return (is_fix(sc, acl, i));
}
