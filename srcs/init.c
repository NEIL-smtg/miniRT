/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:21:11 by suchua            #+#    #+#             */
/*   Updated: 2023/04/26 17:45:13 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_identifier(char **line, t_scene *scene)
{
	if (!*line || !line)
		return ;
	if (!ft_strncmp(*line, "A", 2))
		set_ambient(scene, line);
	else if (!ft_strncmp(*line, "C", 2))
		set_cam(scene, line);
	else if (!ft_strncmp(*line, "L", 2))
		set_light(scene, line);
	else if (!ft_strncmp(*line, "sp", 2))
		set_sphere(scene, line);
	else if (!ft_strncmp(*line, "pl", 2))
		set_plane(scene, line);
	else if (!ft_strncmp(*line, "cy", 2))
		set_cylinder(scene, line);
	ft_free2d(line);
}

int	parse_scene(t_scene *scene, char *file)
{
	int		fd;
	char	*s;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return ;
	s = NULL;
	while (1)
	{
		s = get_next_line(fd);
		if (!s)
			break ;
		parse_identifier(ft_split(s, 32), scene);
		free(s);
	}
}
