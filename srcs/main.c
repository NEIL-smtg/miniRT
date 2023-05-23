/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 00:44:15 by suchua            #+#    #+#             */
/*   Updated: 2023/05/24 03:53:53 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	calc_sphere(t_scene *sc, t_mlx *mlx)
{
	t_vec		sp_dir;
	double		dot;

	if (!sc->sp)
		return ;
	sp_dir = new_vec(
			sc->sp->center.x - sc->cam.pos.x,
			sc->sp->center.y - sc->cam.pos.y,
			sc->sp->center.z - sc->cam.pos.z
			);
	sp_dir = normalize(sp_dir);
	dot = dot_product(sp_dir, sc->cam.vec);
	sc->sp->cd = perspective_projection(
			sp_dir,
			dot,
			(double) mlx->w,
			sc->cam.fov
			);
}

void	calc_plane(t_scene *sc, t_mlx *mlx)
{
	t_vec		pl_dir;
	double		dot;

	if (!sc->pl)
		return ;
	pl_dir = new_vec(
			sc->pl->pos.x - sc->cam.pos.x,
			sc->pl->pos.y - sc->cam.pos.y,
			sc->pl->pos.z - sc->cam.pos.z
			);
	pl_dir = normalize(pl_dir);
	dot = dot_product(pl_dir, sc->cam.vec);
	sc->sp->cd = perspective_projection(
			pl_dir,
			dot,
			(double) mlx->w,
			sc->cam.fov
			);
}

void	draw_sphere(t_scene *sc, t_mlx *mlx)
{
	int	x;
	int	y;

	if (!sc->sp)
		return  ;
	x = sc->sp->cd.screen_x - sc->sp->d / 2 - 1;
	while (++x <= sc->sp->cd.screen_x + sc->sp->d / 2)
	{
		y = sc->sp->cd.screen_y - sc->sp->d / 2 - 1;
		while (++y <= sc->sp->cd.screen_y + sc->sp->d / 2)
		{
			int dx = x - sc->sp->cd.screen_x;
			int dy = y - sc->sp->cd.screen_y;
			if (pow(dx, 2) + pow(dy, 2) <= pow(sc->sp->d / 2, 2))
				mlx_pixel_put(mlx->mlx, mlx->win, x, y, rgb_to_int(sc->sp->rgb));
		}
	}
}

void	draw_plane(t_scene *sc, t_mlx *mlx)
{
	double	x;
	double	y;

	if (!sc->pl)
		return ;
	printf("pl : %f %f\n", sc->pl->cd.screen_x, sc->pl->cd.screen_y);
	x = sc->pl->cd.screen_x;
	while (x < sc->pl->cd.screen_x + WIDTH)
	{
		y = sc->pl->cd.screen_y;
		while (y < sc->pl->cd.screen_y + HEIGHT)
		{
			mlx_pixel_put(mlx->mlx, mlx->win, x, y, rgb_to_int(sc->pl->rgb));
			++y;
		}
		++x;
	}
}

void	drawing_start(t_scene *sc, t_mlx *mlx)
{
	calc_plane(sc, mlx);
	draw_plane(sc, mlx);
	calc_sphere(sc, mlx);
	draw_sphere(sc, mlx);
}

void	mlx_start(t_scene *sc)
{
	t_mlx	mlx;

	mlx.w = WIDTH;
	mlx.h = HEIGHT;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, mlx.w, mlx.h, TITLE);
	drawing_start(sc, &mlx);
	mlx_loop(mlx.mlx);
}

int	main(int ac, char **av)
{
	t_scene	scene;

	if (!valid_arg(ac, av))
		return (1);
	get_input(av[1], &scene);
	mlx_start(&scene);
	return (0);
}
