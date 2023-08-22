/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 01:15:10 by suchua            #+#    #+#             */
/*   Updated: 2023/08/22 17:37:37 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	valid_range(double from, double to, double nb)
{
	return (nb >= from && nb <= to);
}

int	valid_rgb(char *s)
{
	char	**sp;
	int		r;
	int		g;
	int		b;

	sp = ft_split(s, ',');
	if (get_2d_arr_size(sp) != 3 || !valid_num2d(sp))
	{
		ft_free2d(sp);
		return (0);
	}
	r = ft_atof(sp[0]);
	g = ft_atof(sp[1]);
	b = ft_atof(sp[2]);
	ft_free2d(sp);
	return (r >= 0 && r <= 255 && g >= 0
		&& g <= 255 && b >= 0 && b <= 255);
}

int	valid_fov(int fov)
{
	return (fov >= 0 && fov <= 180);
}

int	valid_xyz(char *s)
{
	char	**sp;
	int		flag;

	flag = 1;
	sp = ft_split(s, ',');
	if (get_2d_arr_size(sp) != 3 || !valid_num2d(sp))
		flag = 0;
	ft_free2d(sp);
	return (flag);
}

int	valid_vec3(char *s)
{
	char	**sp;
	double	v1;
	double	v2;
	double	v3;

	sp = ft_split(s, ',');
	if (get_2d_arr_size(sp) != 3 || !valid_num2d(sp))
	{
		ft_free2d(sp);
		return (0);
	}
	v1 = ft_atof(sp[0]);
	v2 = ft_atof(sp[1]);
	v3 = ft_atof(sp[2]);
	ft_free2d(sp);
	return (valid_range(-1, 1, v1) && valid_range(-1, 1, v2)
		&& valid_range(-1, 1, v3));
}
