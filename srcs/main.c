/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 00:44:15 by suchua            #+#    #+#             */
/*   Updated: 2023/05/25 00:17:55 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	mlx_start(t_scene *sc)
{
	t_mlx	mlx;

	return ;
	mlx.w = WIDTH;
	mlx.h = HEIGHT;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, mlx.w, mlx.h, TITLE);
	drawing_start(sc, &mlx);
	mlx_loop(mlx.mlx);
}

static	t_mat	get_transform(t_vec w)
{
	t_vec	u;
	t_vec	v;
	t_mat	mat;

	u = new_vec(0, 1, 0);
	if (w.z == 1.0)
		v = new_vec(1, 0, 0);
	else if (w.z == -1.0)
		v = new_vec(-1, 0, 0);
	else
	{
		u = normalize(new_vec(w.y, -w.x, 0));
		v = cross_product(u, w);
	}
	mat = new_mat(u, v, w);
	return (mat_transposition(mat));
}

t_vec	mat_transformation(t_mat a, t_vec v)
{
	t_mat	t;
	t_vec	new;

	t = mat_transposition(a);
	new.x = dot_product(t.r1, v);
	new.y = dot_product(t.r2, v);
	new.z = dot_product(t.r3, v);
	return (new);
}

void	transform_scaling(t_scene *sc, t_mat transform)
{
	transform_geometric_objs(sc, transform);
	sc->cam.pos = mat_transformation(transform, sc->cam.pos);
	sc->cam.vec = mat_transformation(transform, sc->cam.vec);
}

int	main(int ac, char **av)
{
	t_scene	scene;
	t_mat	transform;

	if (!valid_arg(ac, av))
		return (1);
	get_input(av[1], &scene);
	transform = get_transform(scene.cam.vec);
	transform_scaling(&scene, transform);
	mlx_start(&scene);
	return (0);
}
