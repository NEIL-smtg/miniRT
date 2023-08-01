/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 01:43:56 by suchua            #+#    #+#             */
/*   Updated: 2023/07/30 22:29:43 by suchua           ###   ########.fr       */
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
		else
			printf("CYLINDER\n");
		print_vec3(selected->center, "POSITION");
		if (selected->type != SPHERE)
			print_vec3(selected->dir, "NORMAL");
		return ;
	}
	printf("CAMERA\n");
	print_vec3(cam.pos, "POSITION");
	print_vec3(cam.dir, "NORMAL");
}