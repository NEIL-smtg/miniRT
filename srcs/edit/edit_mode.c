/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:30:19 by mmuhamad          #+#    #+#             */
/*   Updated: 2023/07/28 00:12:48 by suchua           ###   ########.fr       */
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

void	ft_edit(t_viewport *vp)
{
	if (vp->edit)
		return ;
	printf("EDIT MODE....\n");
	vp->edit = true;
	render(vp, *vp->scene);
}
