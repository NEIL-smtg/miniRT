/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:44:09 by suchua            #+#    #+#             */
/*   Updated: 2023/05/23 01:30:20 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	process_line(char *line, t_scene *sc)
{
	if (*line == 'A' || *line == 'a')
		return (set_ambient(&(sc->amblight), line));
	else if (*line == 'C' || *line == 'c')
		return (set_camera(&(sc->cam), line));
	else if (*line == 'L' || *line == 'l')
		return (set_light(&(sc->light), line));
}

int	get_input(char *file, t_scene *sc)
{
	int		fd;
	char	*line;
	int		ret;

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
