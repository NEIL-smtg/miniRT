/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 00:44:15 by suchua            #+#    #+#             */
/*   Updated: 2023/05/23 21:05:29 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"
#include "../include/keys.h"

static void	print_scene(t_scene *sc)
{
	return ;
	printf("A\t{\nfix : %d\nratio : %f\nrgb = %d,%d,%d\n}\n\n", sc->amblight.fix, sc->amblight.ratio, sc->amblight.rgb.r,sc->amblight.rgb.g,sc->amblight.rgb.b);
	printf("Cam\t{\nfix : %d\npos : %f,%f,%f\nvec : %f,%f,%f\nfov = %f\n}\n\n", sc->cam.fix, sc->cam.pos.x,sc->cam.pos.y,sc->cam.pos.z, sc->cam.vec.x,sc->cam.vec.y,sc->cam.vec.z, sc->cam.fov);
	printf("Light\t{\nfix : %d\npos : %f,%f,%f\nbrightness : %f\nrgb = %d,%d,%d\n}\n\n", sc->light.fix, sc->light.pos.x,sc->light.pos.y,sc->light.pos.z, sc->light.brightness, sc->light.rgb.r,sc->light.rgb.g,sc->light.rgb.b);
	
	t_pl	*plt = sc->pl;
	int i = 0;
	while (plt)
	{
		printf("PL_%d\t{\nfix : %d\npos : %f,%f,%f\nvec : %f,%f,%f\nrgb = %d,%d,%d\n}\n\n", i, plt->fix, plt->pos.x, plt->pos.y, plt->pos.z, plt->vec.x, plt->vec.y, plt->vec.z, plt->rgb.r, plt->rgb.g, plt->rgb.b);
		plt = plt->next;
		++i;
	}

	t_sp	*spt = sc->sp;
	i = 0;
	while (spt)
	{
		printf("SP_%d\t{\nfix : %d\npos : %f,%f,%f\ndiameter : %f\nrgb = %d,%d,%d\n}\n\n", i, spt->fix, spt->center.x, spt->center.y, spt->center.z, spt->d,  spt->rgb.r, spt->rgb.g, spt->rgb.b);
		spt = spt->next;
		++i;
	}

	t_cy	*clt = sc->cy;
	i = 0;
	while (clt)
	{
		printf("CY_%d\t{\nfix : %d\npos : %f,%f,%f\nvec : %f,%f,%f\nrgb = %d,%d,%d\ndiameter : %f, height : %f\n}\n\n", i, clt->fix, clt->center.x, clt->center.y, clt->center.z, clt->vec.x, clt->vec.y, clt->vec.z, clt->rgb.r, clt->rgb.g, clt->rgb.b, clt->d, clt->h);
		clt = clt->next;
		++i;
	}
}

t_vec	new_vec(double x, double y, double z)
{
	t_vec	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

double	dot_product(t_vec normal, t_vec direction)
{
	double	dx;
	double	dy;
	double	dz;

	dx = direction.x * normal.x;
	dy = direction.y * normal.y;
	dz = direction.z * normal.z;
	return (dx + dy + dz);
}

void	draw_plane(t_pl *pl, t_mlx *mlx)
{
	int		x;
	int		y;
	double	mag;
	t_vec	normalized;

	mag = sqrt(pow(pl->vec.x, 2) + pow(pl->vec.y, 2) + pow(pl->vec.z, 2));
	normalized = new_vec(pl->vec.x / mag, pl->vec.y / mag, pl->vec.z / mag);
	y = -1;
	while (++y < mlx->h)
	{
		x = -1;
		while (++x < mlx->w)
		{
			if (dot_product(normalized, new_vec(x - pl->pos.x, y - pl->pos.y, -(pl->pos.z)))
				<= 1e-6)
			{
				ft_printf("%d, %d\n", x, y);
				mlx_pixel_put(mlx->mlx, mlx->win, x, y, rgb_to_int(pl->rgb));
			}
		}
	}
}

void	drawing_start(t_scene *sc, t_mlx *mlx)
{
	draw_plane(sc->pl, mlx);
}

void	mlx_start(t_scene *sc)
{
	t_mlx	mlx;

	mlx.w = 1920;
	mlx.h = 1080;
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
	print_scene(&scene);
	mlx_start(&scene);
	return (0);
}
