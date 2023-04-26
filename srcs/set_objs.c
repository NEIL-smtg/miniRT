/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_objs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:47:15 by suchua            #+#    #+#             */
/*   Updated: 2023/04/27 01:24:42 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_objs	*new_sp(char **line)
{
	t_objs	*new;
	char	**val;
 
	new = ft_calloc(1, sizeof(t_objs));
	if (!new)
	{
		error_msg("Fatal : unable to malloc sp");
		return (NULL);
	}
	new->type = SPHERE;
	val = ft_split(line[1], ',');
	new->pos.x = ft_atof(val[0]);
	new->pos.y = ft_atof(val[1]);
	new->pos.z = ft_atof(val[2]);
	ft_free2d(val);
	new->diameter = ft_atof(line[2]);
	new->next = NULL;
	val = ft_split(line[3], ',');
	new->rgb.r = ft_atof(val[0]);
	new->rgb.g = ft_atof(val[1]);
	new->rgb.b = ft_atof(val[2]);
	ft_free2d(val);
	return (new);
}

int	set_sphere(t_scene *scene, char **line)
{
	t_objs	*new;

	if (get_2d_arr_size(line) != 4)
		return (error_msg("Insufficient arguments for sphere")); 
	new = new_sp(line);
	if (!valid_rgb(new->rgb))
	{
		free(new);
		return (0);
	}
	objs_lst_addback(&(scene->objs), &new);
	return (1);
}

t_objs	*new_pl(char **line)
{
	t_objs	*new;
	char	**val;
 
	new = ft_calloc(1, sizeof(t_objs));
	if (!new)
	{
		error_msg("Fatal : unable to malloc sp");
		return (NULL);
	}
	new->type = PLANE;
	val = ft_split(line[1], ',');
	new->pos.x = ft_atof(val[0]);
	new->pos.y = ft_atof(val[1]);
	new->pos.z = ft_atof(val[2]);
	ft_free2d(val);
	val = ft_split(line[2], ',');
	new->vector.x = ft_atof(val[0]);
	new->vector.y = ft_atof(val[1]);
	new->vector.z = ft_atof(val[2]);
	ft_free2d(val);
	val = ft_split(line[3], ',');
	new->rgb.r = ft_atof(val[0]);
	new->rgb.g = ft_atof(val[1]);
	new->rgb.b = ft_atof(val[2]);
	ft_free2d(val);
	new->next = NULL;
	return (new);
}

t_objs	*new_cy(char **line)
{
	t_objs	*new;
	char	**val;
 
	new = ft_calloc(1, sizeof(t_objs));
	if (!new)
	{
		error_msg("Fatal : unable to malloc sp");
		return (NULL);
	}
	new->type = CYLINDER;
	val = ft_split(line[1], ',');
	new->pos.x = ft_atof(val[0]);
	new->pos.y = ft_atof(val[1]);
	new->pos.z = ft_atof(val[2]);
	ft_free2d(val);
	val = ft_split(line[2], ',');
	new->vector.x = ft_atof(val[0]);
	new->vector.y = ft_atof(val[1]);
	new->vector.z = ft_atof(val[2]);
	ft_free2d(val);
	val = ft_split(line[5], ',');
	new->rgb.r = ft_atof(val[0]);
	new->rgb.g = ft_atof(val[1]);
	new->rgb.b = ft_atof(val[2]);
	ft_free2d(val);
	new->diameter = ft_atof(line[3]);
	new->height = ft_atof(line[4]);
	new->next = NULL;
	return (new);
}

int	set_plane(t_scene *scene, char **line)
{
	t_objs	*new;

	if (get_2d_arr_size(line) != 4)
		return (error_msg("Insufficient arguments for sphere")); 
	new = new_pl(line);
	if (!valid_rgb(new->rgb) || !valid_vector(new->vector))
	{
		free(new);
		return (0);
	}
	objs_lst_addback(&(scene->objs), &new);
	return (1);
}

int	set_cylinder(t_scene *scene, char **line)
{
	t_objs	*new;

	if (get_2d_arr_size(line) != 6)
		return (error_msg("Insufficient arguments for sphere")); 
	new = new_cy(line);
	if (!valid_rgb(new->rgb) || !valid_vector(new->vector))
	{
		free(new);
		return (0);
	}
	objs_lst_addback(&(scene->objs), &new);
	return (1);
}