/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:44:09 by suchua            #+#    #+#             */
/*   Updated: 2023/08/01 16:48:31 by suchua           ###   ########.fr       */
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
	else if (!ft_strncmp("co", line, 2))
		return (set_cone(sc, line, LOWCASE));
	else if (!ft_strncmp("CO", line, 2))
		return (set_cone(sc, line, UPCASE));
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
	int	ret;

	ret = 1;
	if (*line == 'A' || *line == 'a')
		acl[0]++;
	if (sc->amblight.fix && acl[0] > 1)
		ret = 0;
	if (*line == 'L' || *line == 'l')
		acl[2]++;
	if (sc->light.fix && acl[2] > 1)
		ret = 0;
	if (!ft_strncmp("CY", line, 2) || !ft_strncmp("cy", line, 2))
		return (1);
	if (!ft_strncmp("CO", line, 2) || !ft_strncmp("co", line, 2))
		return (1);
	if (*line == 'C' || *line == 'c')
		acl[1]++;
	if (sc->cam.fix && acl[1] > 1)
		ret = 0;
	if (!ret)
		free(line);
	return (ret);
}

typedef struct s_v
{
	int	fd;
	int	ret;
	int	i;
	int	*acl;
}	t_v;

int	get_input(char *file, t_scene *sc)
{
	char	*line;
	t_v		v;

	sc->obj = NULL;
	v.fd = open(file, O_RDONLY);
	v.i = 1;
	v.acl = ft_calloc(3, sizeof(int));
	while (1)
	{
		line = get_next_line(v.fd);
		if (!line)
			break ;
		if (!set_acl(line, v.acl, sc))
			break ;
		v.ret = process_line(line, sc);
		free(line);
		++v.i;
		if (!v.ret)
		{
			free(v.acl);
			return (line_error(v.i));
		}
	}	
	return (is_fix(sc, v.acl, v.i));
}
