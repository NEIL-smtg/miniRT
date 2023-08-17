/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 22:07:25 by suchua            #+#    #+#             */
/*   Updated: 2023/08/09 00:38:46 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	luminance(int offset, unsigned char *data)
{
	double	grayscale;

	grayscale = data[offset] * 0.299;
	grayscale += data[offset + 1] * 0.587;
	grayscale += data[offset + 2] * 0.114;
	grayscale /= 255.0;
	return (grayscale);
}

static void	init_bump_map(t_img *texture)
{
	int				x;
	int				y;
	int				offset;
	unsigned char	*data;

	data = (unsigned char *) texture->data_addr;
	y = -1;
	while (++y < texture->height)
	{
		x = -1;
		while (++x < texture->width)
		{
			offset = x * texture->bpp / 8 + y * texture->line_size;
			texture->bump_map[y][x] = luminance(offset, data);
		}
	}
}

static void	**new_2d_arr(int h, int w, size_t s1, size_t s2)
{
	void	**new;
	int		i;

	new = ft_calloc((size_t) h, s1);
	if (!new)
		return (NULL);
	i = -1;
	while (++i < h)
		new[i] = ft_calloc((size_t) w, s2);
	return (new);
}

void	init_texture(char *xpm, t_img *texture, void *mlx)
{
	texture->ptr = NULL;
	texture->bump_map = NULL;
	if (!xpm)
		return ;
	texture->ptr = mlx_xpm_file_to_image(
			mlx,
			xpm,
			&texture->width,
			&texture->height
			);
	texture->data_addr = mlx_get_data_addr(
			texture->ptr,
			&texture->bpp,
			&texture->line_size,
			&texture->endian
			);
	texture->bump_map = (double **) new_2d_arr(
			texture->height,
			texture->width,
			sizeof(double *),
			sizeof(double)
			);
	init_bump_map(texture);
}
