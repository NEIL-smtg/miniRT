/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 00:44:15 by suchua            #+#    #+#             */
/*   Updated: 2023/04/26 17:22:55 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	arg_error(int ac)
{
	if (ac < 3)
		ft_putendl_fd("Lack of arguments", 2);
	else
		ft_putendl_fd("Too many arguments", 2);
	ft_putendl_fd("Usage : ./miniRT <scenes.rt>", 2);
	return (1);
}

int	valid_scene(char *file)
{
	char	*tmp;
	int		fd;

	tmp = ft_strrchr(file, '.');
	if (!tmp || ft_strncmp(tmp, ".rt", 4))
	{
		ft_putendl_fd("Usage : ./miniRT <scenes.rt>", 2);
		return (0);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("file");
		ft_putendl_fd("Usage : ./miniRT <scenes.rt>", 2);
		return (0);
	}
	close(fd);
	return (1);
}

int	main(int ac, char **av)
{
	t_scene	scene;

	if (ac != 2)
		return (arg_error(ac));
	if (!valid_scene(av[1]))
		return (1);
	if (parse_scene(&scene, av[1]) == -1)
		return (1);
	return (0);
}
