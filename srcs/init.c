/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:21:11 by suchua            #+#    #+#             */
/*   Updated: 2023/04/27 01:28:26 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_identifier(char **line, t_scene *scene)
{
	if (!*line || !line)
		return (1);
	if (!ft_strncmp(*line, "A", 2))
		return (set_ambient(scene, line));
	else if (!ft_strncmp(*line, "C", 2))
		return (set_cam(scene, line));
	else if (!ft_strncmp(*line, "L", 2))
		return (set_light(scene, line));
	else if (!ft_strncmp(*line, "sp", 2))
		return (set_sphere(scene, line));
	else if (!ft_strncmp(*line, "pl", 2))
		return (set_plane(scene, line));
	else if (!ft_strncmp(*line, "cy", 2))
		return (set_cylinder(scene, line));
	return (1);
}

int	parse_scene(t_scene *scene, char *file)
{
	int		fd;
	char	*s;
	char	**line;
	int		ret;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	s = NULL;
	scene->objs = NULL;
	while (1)
	{
		s = get_next_line(fd);
		if (!s)
			break ;
		line = ft_split(s, 32);
		ret = parse_identifier(line, scene);
		free(s);
		ft_free2d(line);
		if (!ret)
			return (0);
	}
	return (1);
}

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, 500, 500, "miniRT");
	mlx_loop(mlx->mlx);
}
