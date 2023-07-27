/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 02:03:41 by suchua            #+#    #+#             */
/*   Updated: 2023/07/27 23:31:45 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	clean_img(t_viewport *vp)
{
	size_t	size;

	size = (size_t)((int) vp->h * vp->img.line_size);
	size += (size_t)((int) vp->w * (vp->img.bpp / 16));
	ft_memset(vp->img.data_addr, 0, size);
	mlx_clear_window(vp->mlx, vp->win);
}

double	get_radian(int angle)
{
	return ((double) angle * M_PI / 180);
}
