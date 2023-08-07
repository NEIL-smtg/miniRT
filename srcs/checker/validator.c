/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 01:53:18 by suchua            #+#    #+#             */
/*   Updated: 2023/08/07 22:06:41 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	prompt_usage_error(void)
{
	ft_putendl_fd("Invalid number of arguments !!", 2);
	ft_putendl_fd("Usage : ./miniRT <path_to_scene.rt>", 2);
	ft_putendl_fd("or", 2);
	ft_putstr_fd("Usage : ./miniRT <path_to_scene.rt> ", 2);
	ft_putendl_fd("<path_to_texture.xpm>", 2);
	return (0);
}

static int	prompt_invalid_file(void)
{
	ft_putendl_fd("Invalid file !!", 2);
	ft_putendl_fd("Scene file must be in .rt format !!", 2);
	ft_putendl_fd("Texture file must be in .xpm format !!", 2);
	return (0);
}

static int	valid_rt(char *file, char *format)
{
	int	start;
	int	fd;

	start = ft_strlen(file) - ft_strlen(format);
	if (start < 0 || ft_strncmp(format, file + start, 3))
		return (prompt_invalid_file());
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Error : No such file or directory.", 2);
		return (0);
	}
	else
	{
		ft_putstr_fd(format + 1, 1);
		ft_putendl_fd(" file received...", 1);
	}
	close(fd);
	return (1);
}

int	valid_arg(int ac, char **av)
{
	if (ac != 2 && ac != 3)
		return (prompt_usage_error());
	if (!valid_rt(av[1], ".rt"))
		return (0);
	if (av[2] && !valid_rt(av[2], ".xpm"))
		return (0);
	return (1);
}
