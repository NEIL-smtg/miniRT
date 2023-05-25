/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 00:44:15 by suchua            #+#    #+#             */
/*   Updated: 2023/05/25 23:47:41 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	mlx_start(t_mlx *mlx)
{
	double	aspect_ratio;

	aspect_ratio = 16.0 / 9.0;	
	mlx->w = 400;
	mlx->h = (int) (mlx->w * aspect_ratio);

	t_vec	origin = new_vec(0, 0, 0);
	double	viewport_height = 2.0;
	double	viewport_width = aspect_ratio * viewport_height;
	double	focal_len = 1.0;
	t_vec	horizontal = new_vec(viewport_width, 0, 0);
	t_vec	vertical = new_vec(0, viewport_height, 0);
	t_vec	corner;
	
	corner = new_vec(origin.x - horizontal.x / 2, origin.y - vertical.y / 2, origin.z - focal_len);
	printf("%f %f\n", corner.x, corner.y);

	t_img	img;

	mlx->mlx = mlx_init();
	img.img_ptr = mlx_new_image(mlx->mlx, mlx->w, mlx->h);
	img.data_addr = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.line_size, &img.endian);
	
	int		x;
	int		y;
	int		size = img.bpp / 8;

	y = mlx->h;
	while (--y >= 0)
	{
		x = mlx->w;
		while (--x >= 0)
		{
			int	offset = (y * img.line_size) + (x * size);
			img.data_addr[offset + 2] = 255;
			img.data_addr[offset + 1] = 0;
			img.data_addr[offset] = 0;
		}
	}
	mlx->win = mlx_new_window(mlx->mlx, mlx->w, mlx->h, "miniRT");
	mlx_put_image_to_window(mlx->mlx, mlx->win, img.img_ptr, 0, 0);
}

int	main(int ac, char **av)
{
	t_scene	scene;
	t_mlx	mlx;

	if (!valid_arg(ac, av))
		return (1);
	get_input(av[1], &scene);
	mlx_start(&mlx);
	return (0);
}
