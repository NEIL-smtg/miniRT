/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 01:14:04 by suchua            #+#    #+#             */
/*   Updated: 2023/07/15 01:14:14 by suchua           ###   ########.fr       */
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
	s = rt_split(line);
	if (get_2d_arr_size(s) != 3 || !valid_range(0, 1, ft_atof(s[1]))
		|| !valid_rgb(s[2]))
	{
		ft_putstr_fd("Error !!\nInvalid arguments for ambient.", 2);
		ft_free2d(s);
		return (0);
	}
	al->ratio = ft_atof(s[1]);
	color = ft_split(s[2], ',');
	al->rgb.r = ft_atof(color[0]);
	al->rgb.g = ft_atof(color[1]);
	al->rgb.b = ft_atof(color[2]);
	ft_free2d(color);
	ft_free2d(s);
	return (1);
}

static int	valid_cam(char **sp)
{
	int	flag;

	flag = 1;
	if (get_2d_arr_size(sp) != 4 || !valid_xyz(sp[1])
		|| !valid_vec3(sp[2]) || !valid_fov(ft_atoi(sp[3])))
	{
		flag = 0;
	}
	ft_free2d(sp);
	return (flag);
}

int	set_camera(t_camera *cam, char *line)
{
	char	**sp;
	char	**xyz;

	cam->fix = 0;
	if (*line == 'C')
		cam->fix = 1;
	if (!valid_cam(rt_split(line)))
	{
		ft_putstr_fd("Error !!\nInvalid arguments for camera.", 2);
		return (0);
	}
	sp = rt_split(line);
	cam->fov = get_radian(ft_atoi(sp[3]));
	xyz = ft_split(sp[1], ',');
	cam->pos.x = ft_atof(xyz[0]);
	cam->pos.y = ft_atof(xyz[1]);
	cam->pos.z = ft_atof(xyz[2]);
	ft_free2d(xyz);
	xyz = ft_split(sp[2], ',');
	cam->dir.x = ft_atof(xyz[0]);
	cam->dir.y = ft_atof(xyz[1]);
	cam->dir.z = ft_atof(xyz[2]);
	ft_free2d(xyz);
	ft_free2d(sp);
	return (1);
}

static int	valid_light(char **s)
{
	int		size;
	int		flag;

	size = get_2d_arr_size(s);
	flag = 1;
	if (size != 3 && size != 4)
		flag = 0;
	if (!valid_xyz(s[1]))
		flag = 0;
	if (!valid_range(0, 1, ft_atof(s[2])))
		flag = 0;
	if (size == 4 && !valid_rgb(s[3]))
		flag = 0;
	ft_free2d(s);
	return (flag);
}

int	set_light(t_light *lg, char *line)
{
	char	**sp;
	char	**xyz;

	lg->fix = 0;
	if (*line == 'L')
		lg->fix = 1;
	if (!valid_light(rt_split(line)))
	{
		ft_putstr_fd("Error !!\nInvalid arguments for light.", 2);
		return (0);
	}
	sp = rt_split(line);
	xyz = ft_split(sp[1], ',');
	lg->pos.x = ft_atof(xyz[0]);
	lg->pos.y = ft_atof(xyz[1]);
	lg->pos.z = ft_atof(xyz[2]);
	ft_free2d(xyz);
	lg->brightness = ft_atof(sp[2]);
	xyz = ft_split(sp[3], ',');
	lg->rgb.r = ft_atof(xyz[0]);
	lg->rgb.g = ft_atof(xyz[1]);
	lg->rgb.b = ft_atof(xyz[2]);
	ft_free2d(xyz);
	ft_free2d(sp);
	return (1);
}
