/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 01:14:04 by suchua            #+#    #+#             */
/*   Updated: 2023/05/23 01:31:07 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	set_ambient(t_amblight *al, char *line)
{
	char	**s;
	char	**color;

	al->fix = 0;
	if (*line == 'A')
		al->fix = 1;
	s = ft_split(line, 32);
	if (get_2d_arr_size(s) != 3 || !valid_range(0, 1, ft_atof(s[1]))
		|| !valid_rgb(s[2]))
	{
		ft_free2d(s);
		return (0);
	}
	al->ratio = ft_atof(s[1]);
	color = ft_split(s[2], ',');
	al->rgb.r = ft_atoi(color[0]);
	al->rgb.g = ft_atoi(color[1]);
	al->rgb.b = ft_atoi(color[2]);
	ft_free2d(color);
	ft_free2d(s);
	return (1);
}

int	set_camera(t_camera *cam, char *line)
{
	char	**sp;
	char	**xyz;

	cam->fix = 0;
	if (*line == 'A')
		cam->fix = 1;
	sp = ft_split(line, 32);
	if (get_2d_arr_size(sp) != 4 || !valid_fov(ft_atoi(line[3]))
			|| !valid_vec3(line[2]))
	{
		ft_free2d(sp);
		return (0);
	}
	cam->fov = ft_atof(line[3]);
	xyz = ft_split(line[1], ',');
	cam->pos.x = ft_atof(xyz[0]);
	cam->pos.y = ft_atof(xyz[1]);
	cam->pos.z = ft_atof(xyz[2]);
	ft_free2d(xyz);
	xyz = ft_split(line[2], ',');
	cam->vec.x = ft_atof(xyz[0]);
	cam->vec.y = ft_atof(xyz[1]);
	cam->vec.z = ft_atof(xyz[2]);
	ft_free2d(xyz);
	return (1);
}

int	set_light(t_light *lg, char *line)
{
	char	**sp;
	char	**xyz;

	lg->fix = 0;
	if (*line == 'A')
		lg->fix = 1;
	sp = ft_split(line, 32);
	if (get_2d_arr_size(sp) != 4 || !valid_fov(ft_atoi(line[3]))
			|| !valid_vec3(line[2]))
	{
		ft_free2d(sp);
		return (0);
	}
}
