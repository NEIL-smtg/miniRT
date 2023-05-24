/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 00:44:15 by suchua            #+#    #+#             */
/*   Updated: 2023/05/24 17:18:17 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cd	*calc_2d_coordinate(t_camera cam, t_pos pos)
{
	t_cd	*new;
	t_vec	direction;
	double	dot;

	direction = new_vec(
				pos.x - cam.pos.x,
				pos.y - cam.pos.y,
				pos.z - cam.pos.z
				);
	direction = normalize(direction);
	dot = dot_product(direction, cam.vec);
	if (dot <= 0.0f)
		return (NULL);
	new = perspective_projection(direction, dot, cam.fov);
	return (new);
}

void	draw_sphere(t_sp *sp, t_mlx *mlx)
{
	int		x;
	int		y;
	double	dx;
	double	dy;

	x = sp->cd->screen_x - sp->d / 2 - 1;
	while (++x <= sp->cd->screen_x + sp->d / 2)
	{
		y = sp->cd->screen_y - sp->d / 2 - 1;
		while (++y <= sp->cd->screen_y + sp->d / 2)
		{
			dx = x - sp->cd->screen_x;
			dy = y - sp->cd->screen_y;
			if (pow(dx, 2) + pow(dy, 2) <= pow(sp->d / 2, 2))
				mlx_pixel_put(mlx->mlx, mlx->win, x, y, rgb_to_int(sp->rgb));
		}
	}
}

void	draw_plane(t_pl *pl, t_mlx *mlx)
{
	double	x;
	double	y;

	x = pl->cd->screen_x;
	while (x < pl->cd->screen_x + WIDTH)
	{
		y = pl->cd->screen_y;
		while (y < pl->cd->screen_y + HEIGHT)
		{
			mlx_pixel_put(mlx->mlx, mlx->win, x, y, rgb_to_int(pl->rgb));
			++y;
		}
		++x;
	}
}

void	draw_cylinder(t_cy *cy, t_mlx *mlx)
{
	int     x;
	int		y;
	double	angle;
	double	step = 0.1;

	// Draw the circle at the center position
	for (angle = 0.0; angle < 2 * M_PI; angle += step)
	{
		x = cy->cd->screen_x + cy->d / 2 * cos(angle);
		y = cy->cd->screen_y + cy->d / 2 * sin(angle);

		mlx_pixel_put(mlx->mlx, mlx->win, x, y, rgb_to_int(cy->rgb)); // Example: Set color to white
	}

	// Draw vertical lines connecting the top and bottom points
	int top_y = cy->cd->screen_y - cy->h / 2;
	int bottom_y = cy->cd->screen_y + cy->h / 2;

	for (x = cy->cd->screen_x - cy->d / 2; x <= cy->cd->screen_x + cy->d / 2; x++)
	{
		mlx_pixel_put(mlx->mlx, mlx->win, x, top_y, rgb_to_int(cy->rgb)); // Example: Set color to white
		mlx_pixel_put(mlx->mlx, mlx->win, x, bottom_y, rgb_to_int(cy->rgb)); // Example: Set color to white
	}
}

void	drawing_start(t_scene *sc, t_mlx *mlx)
{
	t_pl	*t1;
	t_sp	*t2;
	t_cy	*t3;

	t1 = sc->pl;
	t2 = sc->sp;
	t3 = sc->cy;
	while (t1)
	{
		t1->cd = calc_2d_coordinate(sc->cam, t1->pos);
		if (t1->cd)
			draw_plane(t1, mlx);
		t1 = t1->next;
	}
	while (t2)
	{
		t2->cd = calc_2d_coordinate(sc->cam, t2->center);
		if (t2->cd)
			draw_sphere(t2, mlx);
		t2 = t2->next;
	}
	// while (t3)
	// {
	// 	t3->cd = calc_2d_coordinate(sc->cam, t3->center);
	// 	if (t3->cd)
	// 		draw_cylinder(t3, mlx);
	// 	t3 = t3->next;
	// }
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
