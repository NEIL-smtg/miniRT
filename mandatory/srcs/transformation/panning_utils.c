/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panning_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:38:04 by mmuhamad          #+#    #+#             */
/*   Updated: 2023/08/16 16:06:49 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	panning(int key, t_viewport *vp)
{
	if (vp->selected && (vp->selected->type == SPHERE
			|| vp->selected->type == LIGHT))
	{
		printf("\nSphere and light cannot be rotated !!\n");
		printf("Please choose CYLINDER, CONE or PLANE for rotation.\n\n");
		return ;
	}
	else
		start_panning(key, vp);
	transformation_info(vp->selected, vp->scene->cam);
}
