/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 22:57:43 by suchua            #+#    #+#             */
/*   Updated: 2023/08/07 00:55:44 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_viewport(t_viewport *vp, t_camera cam)
{
	vp->aspect_ratio = 16.0 / 9.0;
	vp->h = HEIGHT;
	vp->w = HEIGHT * vp->aspect_ratio;
	vp->focal = tan(cam.fov / 2);
	vp->view_mat = get_view_matrix(cam);
	vp->inv_view_mat = inverse_mat4(vp->view_mat);
}

void	create_mlx(t_viewport *vp, t_scene *scene, char *file)
{
	vp->mlx = mlx_init();
	vp->win = mlx_new_window(vp->mlx, (int) vp->w, (int) vp->h, TITLE);
	vp->img.ptr = mlx_new_image(vp->mlx, (int) vp->w, (int) vp->h);
	vp->img.data_addr = mlx_get_data_addr(
			vp->img.ptr,
			&vp->img.bpp,
			&vp->img.line_size,
			&vp->img.endian
			);
	vp->scene = scene;
	vp->selected = NULL;
	vp->edit = false;
	vp->checkerboard = false;
}

void	init_texture(char *file, t_viewport *vp)
{
	if (!file)
	{
		vp->texture.ptr = NULL;
		printf("No texture loaded.\n");
		return ;
	}
	vp->texture.ptr = mlx_xpm_file_to_image(vp->mlx, file, \
			&(vp->texture.width),
			&(vp->texture.height)
		);
	vp->texture.data_addr = mlx_get_data_addr(vp->texture.ptr,
		&vp->texture.bpp,
		&vp->texture.line_size,
		&vp->texture.endian
	);
}

void	init_bump(t_img *texture)
{
	int		p[2];
	int		offset;
	double	grayscale;
	
	texture->bump_map = ft_calloc((size_t) texture->height, sizeof(double *));
	p[0] = -1;
	while (++p[0] < texture->height)
		texture->bump_map[p[0]] = ft_calloc((size_t) texture->width, sizeof(double));
	p[0] = -1;
	while (++p[0] < texture->height)
	{
		p[1] = -1;
		while (++p[1] < texture->width)
		{
			offset = p[0] * texture->line_size + p[1] * (texture->bpp / 8);
			grayscale = texture->data_addr[offset];
			grayscale += texture->data_addr[offset + 1];
			grayscale += texture->data_addr[offset + 2];
			grayscale /= (3.0 * 255.0);
			texture->bump_map[p[0]][p[1]] = grayscale;
		}
	}
}

int	main(int ac, char **av)
{
	t_scene		scene;
	t_viewport	vp;

	if (!valid_arg(ac, av))
		exit (1);
	if (!get_input(av[1], &scene))
		exit (1);
	init_viewport(&vp, scene.cam);
	world_to_camera(vp.inv_view_mat, &scene);
	// print_scene(&scene);
	create_mlx(&vp, &scene, av[2]);
	init_texture(av[2], &vp);
	init_bump(&vp.texture);
	render(&vp, scene);
	hooks(&vp);
	exit (0);
}
