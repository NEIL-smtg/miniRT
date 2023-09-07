/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neilsundae <suchua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 02:03:41 by suchua            #+#    #+#             */
/*   Updated: 2023/09/08 02:28:28 by neilsundae       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// exit with error message s1 or/with s2
void	ft_error(char *s1, char *s2)
{
	printf("Error!\n");
	printf("%s", s1);
	if (s2)
		printf("%s", s1);
	printf("\n");
	exit(1);
}

void	clean_img(t_viewport *vp)
{
	size_t	size;

	size = (size_t)((int) vp->h * vp->img.line_size);
	size += (size_t)((int) vp->w * (vp->img.bpp / 8));
	ft_memset(vp->img.data_addr, 0, size);
	mlx_clear_window(vp->mlx, vp->win);
}

double	get_radian(int angle)
{
	return ((double) angle * M_PI / 180);
}

double	nb_clamp(double n, double min, double max)
{
	if (n < min)
		return (min);
	if (n > max)
		return (max);
	return (n);
}
