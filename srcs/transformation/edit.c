/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:30:19 by mmuhamad          #+#    #+#             */
/*   Updated: 2023/07/27 19:37:34 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_rgb	get_selected_color(t_rgb c)
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

void	render_edit(t_viewport *vp, t_scene sc)
{
	int		pixel[2];
	t_ray	ray;
	t_obj	*closest;
	double	t;

	if (vp->edit)
		clean_img(vp);
	ray.origin = sc.cam.pos;
	pixel[1] = 0;
	while (pixel[1] < (int) vp->h)
	{
		pixel[0] = 0;
		while (pixel[0] < (int) vp->w)
		{
			closest = NULL;
			ray.dir = get_ray_dir(pixel, vp, ray.origin);
			t = get_closest_obj(ray, sc.obj, &closest);
			if (vp->selected && vp->selected == closest)
				fill_color(vp->selected->tmp_color, vp, pixel);
			else if (closest)
				fill_color(closest->rgb, vp, pixel);
			pixel[0] += 3;
		}
		pixel[1] += 3;
	}
	mlx_put_image_to_window(vp->mlx, vp->win, vp->img.ptr, 0, 0);
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

int	mouse_event(int button, int x, int y, t_viewport *vp)
{
	int		pixel[2];
	t_ray	ray;

	printf("Mouse clicked\n");
	if (!vp->edit)
		return (0);
	pixel[0] = x;
	pixel[1] = y;
	vp->selected = NULL;
	ray.origin = vp->scene->cam.pos;
	ray.dir = get_ray_dir(pixel, vp, ray.origin);
	get_closest_obj(ray, vp->scene->obj, &vp->selected);
	selected_msg(vp->selected);
	if (!vp->selected)
		return (0);
	vp->selected->edit_d = false;
	vp->selected->edit_h = false;
	vp->selected->tmp_color = get_selected_color(vp->selected->rgb);
	render_edit(vp, *vp->scene);
	return (0);
}

void	ft_edit(t_viewport *vp)
{
	if (vp->edit)
		return ;
	printf("EDIT MODE....\n");
	vp->edit = true;
	render_edit(vp, *vp->scene);
}
