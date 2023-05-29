/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 00:44:15 by suchua            #+#    #+#             */
/*   Updated: 2023/05/28 19:14:01 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdbool.h>

bool	hit_sp(t_sp *sp, t_vec origin, t_vec raydir)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = new_vec
		(
			origin.x - sp->center.x,
			origin.y - sp->center.y,
			origin.z - sp->center.z
			);
	a = dot_product(raydir, raydir);
	b = 2.0 * dot_product(oc, raydir);
	c = dot_product(oc, oc) - pow(sp->d / 2, 2);
	discriminant = b * b - 4 * a * c;
	return (discriminant > 0);
}

void	fill_pixel(t_img *img, double x, double y, t_rgb rgb)
{
	int				index;
	unsigned char	*pixel;

	pixel = (unsigned char *) img->data_addr;
	index = ((int) x * img->bpp / 8) + ((int) y * img->line_size);
	pixel[index] = rgb.b;
	pixel[index + 1] = rgb.g;
	pixel[index + 2] = rgb.r;
	pixel[index + 3] = 0;
}

void	get_intersects(t_viewport *vp, double x, double y, t_scene sc)
{
	double	u;
	double	v;
	t_vec	raydir;

	while (sc.sp)
	{
		u = x / vp->w;
		v = y / vp->h;
		raydir = get_raydir(u, v, *vp);
		if (hit_sp(sc.sp, vp->origin, raydir))
			fill_pixel(vp->img, x, y, sc.sp->rgb);
		sc.sp = sc.sp->next;
	}
}

void	fill_img(t_viewport *vp, t_scene sc)
{
	double	x;
	double	y;

	y = vp->h + 1;
	while (--y >= 0.0)
	{
		x = -1;
		while (++x < vp->w)
		{
			get_intersects(vp, x, y, sc);
		}
	}
}

void	mlx_start(t_viewport *vp, t_scene sc)
{
	t_img	img;

	vp->mlx = mlx_init();
	img.img_ptr = mlx_new_image(vp->mlx, (int) vp->w, (int) vp->h);
	img.data_addr = mlx_get_data_addr(
			img.img_ptr,
			&img.bpp,
			&img.line_size,
			&img.endian
			);
	vp->img = &img;
	fill_img(vp, sc);
	vp->win = mlx_new_window(vp->mlx, (int) vp->w, (int) vp->h, TITLE);
	mlx_put_image_to_window
	(
		vp->mlx, vp->win,
		vp->img->img_ptr,
		0, 0
	);
	mlx_loop(vp->mlx);
}

void	init_viewport(t_viewport *vp, t_camera cam)
{
	vp->aspect_ratio = 16.0 / 9.0;
	vp->h = HEIGHT;
	vp->w = HEIGHT * vp->aspect_ratio;
	vp->focal = get_focal_length(cam.fov, vp->w);
	vp->horizontal = new_vec(vp->w, 0, 0);
	vp->vertical = new_vec(0, vp->h, 0);
	vp->origin = cam.pos;
	vp->corner = new_vec(
			vp->origin.x - vp->w / 2,
			vp->origin.y - vp->h / 2,
			vp->origin.z - vp->focal
			);
}

int	main(int ac, char **av)
{
	t_scene		scene;
	t_viewport	vp;

	if (!valid_arg(ac, av))
		return (1);
	get_input(av[1], &scene);
	init_viewport(&vp, scene.cam);
	mlx_start(&vp, scene);
	return (0);
}
