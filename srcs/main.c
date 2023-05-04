/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 00:44:15 by suchua            #+#    #+#             */
/*   Updated: 2023/05/04 02:08:00 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"
#include "../include/keys.h"

int	destroy_exit(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
	return (0);
}

int	key_on_pressed(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	return (1);	
}

int	main(int ac, char **av)
{
	t_mlx	mlx;
	t_scene	scene;

	if (!valid_arg(ac, av))
		return (1);
	// mlx_hook(mlx.win, KEY_PRESS, (1L << 0), key_on_pressed, &mlx);
	// mlx_hook(mlx.win, CLOSE_WINDOW, (1L << 0), destroy_exit, &mlx);
	// mlx_loop(mlx.mlx);
	return (0);
}
