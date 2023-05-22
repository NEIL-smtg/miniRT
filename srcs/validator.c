/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 01:53:18 by suchua            #+#    #+#             */
/*   Updated: 2023/05/22 20:33:13 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	prompt_usage_error(void)
{
	ft_putendl_fd("Invalid number of arguments !!", 2);
	ft_putendl_fd("Usage : ./miniRT <path_to_scene.rt>", 2);
	return (0);
}

static int	prompt_invalid_file(void)
{
	ft_putendl_fd("Invalid file !!", 2);
	ft_putendl_fd("File must be in .rt format !!", 2);
	return (0);
}

static int	prompt_save_error(void)
{
	ft_putendl_fd("Invalid input !!", 2);
	ft_putendl_fd("Usage : ./miniRT <path_to_scene.rt> --save", 2);
	return (0);
}

static int	valid_rt(char *file)
{
	int	start;
	int	fd;

	start = ft_strlen(file) - 3;
	if (start < 0 || ft_strncmp(".rt", file + start, 3))
		return (prompt_invalid_file());
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Error : No such file or directory.", 2);
		return (0);
	}
	else
		ft_putendl_fd("File received...", 1);
	close(fd);
	return (1);
}

int	valid_arg(int ac, char **av)
{
	if (ac != 2 && ac != 3)
		return (prompt_usage_error());
	if (!valid_rt(av[1]))
		return (0);
	if (ac == 3 && ft_strncmp(av[2], "--save", 7))
		return (prompt_save_error());
	return (1);
}
