/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:45:37 by suchua            #+#    #+#             */
/*   Updated: 2023/04/27 01:17:37 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	set_ambient(t_scene *scene, char **line)
{
	char	**rgb;

	if (get_2d_arr_size(line) != 3)
		return (error_msg("incorrect number of arguments for ambient"));
	scene->amblight.ratio = ft_atof(line[1]);
	rgb = ft_split(line[2], ',');
	scene->amblight.rgb.r = ft_atoi(rgb[0]);
	scene->amblight.rgb.g = ft_atoi(rgb[1]);
	scene->amblight.rgb.b = ft_atoi(rgb[2]);
	ft_free2d(rgb);
	if (scene->amblight.ratio < 0.0f || scene->amblight.ratio > 1.0f)
		return (error_msg("Wrong ratio for ambient light\nUsage : (0.0 - 1.0)"));
	return (valid_rgb(scene->amblight.rgb));
}

int	set_cam(t_scene *scene, char **line)
{
	char	**val;

	if (get_2d_arr_size(line) != 4)
		return (error_msg("incorrect number of arguments for camera"));
	val = ft_split(line[1], ',');
	scene->cam.pos.x = ft_atof(val[0]);
	scene->cam.pos.y = ft_atof(val[1]);
	scene->cam.pos.z = ft_atof(val[2]);
	ft_free2d(val);
	val = ft_split(line[2], ',');
	scene->cam.vector.x = ft_atof(val[0]);
	scene->cam.vector.y = ft_atof(val[1]);
	scene->cam.vector.z = ft_atof(val[2]);
	ft_free2d(val);
	scene->cam.fov = ft_atoi(line[2]);
	return (valid_camera(scene->cam));
}

int	set_light(t_scene *scene, char **line)
{
	char	**val;

	if (get_2d_arr_size(line) != 3 && get_2d_arr_size(line) != 4)
		return (error_msg("incorrect number of arguments for camera"));
	val = ft_split(line[1], ',');
	scene->light.pos.x = ft_atof(val[0]);
	scene->light.pos.y = ft_atof(val[1]);
	scene->light.pos.z = ft_atof(val[2]);
	ft_free2d(val);
	scene->light.brightness = ft_atof(line[2]);
	if (line[3])
	{
		val = ft_split(line[3], ',');
		scene->light.rgb.r = ft_atof(val[0]);
		scene->light.rgb.g = ft_atof(val[1]);
		scene->light.rgb.b = ft_atof(val[2]);
		ft_free2d(val);
	}
	return (valid_light(scene->light, get_2d_arr_size(line)));
}
