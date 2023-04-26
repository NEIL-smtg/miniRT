/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validater.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 01:20:03 by suchua            #+#    #+#             */
/*   Updated: 2023/04/27 01:22:46 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	valid_rgb(t_rgb rgb)
{
	if (rgb.r < 0 || rgb.r > 255 || rgb.g < 0 || rgb.g > 255
			|| rgb.b < 0 || rgb.b > 255)
	{
		error_msg("Wrong values for rgb\n Usage: 0-255");
		return (0);		
	}
	return (1);
}

int	valid_vector(t_vector vector)
{
	int	flag;
	
	flag = 1;
	if (vector.x < -1.0f || vector.x > 1.0f)
		flag = 0;
	if (vector.y < -1.0f || vector.y > 1.0f)
		flag = 0;
	if (vector.z < -1.0f || vector.z > 1.0f)
		flag = 0;
	if (!flag)
		error_msg("Invalid vector !\nUsage : [0.0 - 1.0]");
	return (flag);
}

int	valid_camera(t_camera cam)
{
	int		flag;

	flag = valid_vector(cam.vector);
	if (cam.fov < 0 || cam.fov > 180)
		flag = 0;
	if (!flag)
		error_msg("Wrong argument values for cameara");
	return (flag);
}

int	valid_light(t_light light, int size)
{
	int	flag;

	flag = 1;
	if (light.brightness < 0.0f || light.brightness > 1.0f)
		flag = 0;
	if (size == 4)
		flag = valid_rgb(light.rgb);
	if (!flag)
		error_msg("Wrong arguments valus for light");
	return (flag);
}
