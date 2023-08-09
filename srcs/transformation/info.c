/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 01:43:56 by suchua            #+#    #+#             */
/*   Updated: 2023/08/09 11:22:32 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	transformation_info(t_obj *selected, t_camera cam)
{
	printf("\nAfter transformation :\n");
	if (selected)
	{
		if (selected->type == SPHERE)
			printf("SPHERE\n");
		else if (selected->type == PLANE)
			printf("PLANE\n");
		else if (selected->type == CYLINDER)
			printf("CYLINDER\n");
		else if (selected->type == LIGHT)
			printf("LIGHT\n");
		else
			printf("CONE\n");
		print_vec3(selected->center, "POSITION");
		if (selected->type != SPHERE && selected->type != LIGHT)
			print_vec3(selected->dir, "NORMAL");
		return ;
	}
	printf("CAMERA\n");
	print_vec3(cam.pos, "POSITION");
	print_vec3(cam.dir, "NORMAL");
}
