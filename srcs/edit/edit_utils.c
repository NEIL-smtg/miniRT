/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 22:40:46 by suchua            #+#    #+#             */
/*   Updated: 2023/07/29 22:43:56 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	get_selected_color(t_rgb c)
{
	double	min;
	double	max;

	min = fmin(c.r, c.g);
	min = fmin(min, c.b);
	max = fmax(c.r, c.g);
	max = fmax(max, c.b);
	if (min == c.r)
		c.r = max;
	else if (max == c.r)
		c.r = min;
	if (min == c.g)
		c.g = max;
	else if (max == c.g)
		c.g = min;
	if (min == c.b)
		c.b = max;
	else if (max == c.b)
		c.b = min;
	return (c);
}

void	selected_msg(t_obj *selected)
{
	if (!selected)
		printf("\nYou are in CAMERA mode.\n");
	else if (selected->type == SPHERE)
		printf("\nSPHERE selected\n");
	else if (selected->type == PLANE)
		printf("\nPLANE selected\n");
	else if (selected->type == CYLINDER)
		printf("\nCYLINDER selected\n");
	printf("Press:\n\tkey 1-6 for rotation\n");
	printf("\tWASD↑↓ for translation.\n");
	if (!selected)
		return ;
	printf("\tcombination : h,+ to increase height\n");
	printf("\tcombination : h,- to increase height\n");
	printf("\tcombination : j,+ to increase diameter\n");
	printf("\tcombination : j,- to increase diameter\n");
}

static void	edit_info_msg(void)
{
	printf("\n\n####### EDIT MODE #######\n");
	printf("Press:\n\tkey C to switch back to CAMERA mode\n");
	printf("\tkey R to apply edit and RENDER again\n");
	printf("\nClicked:\n\tClick object to edit its properties\n");
}

void	ft_edit(t_viewport *vp)
{
	if (vp->edit)
		return ;
	edit_info_msg();
	selected_msg(vp->selected);
	vp->edit = true;
	render(vp, *vp->scene);
}
