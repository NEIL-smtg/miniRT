/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:47:56 by suchua            #+#    #+#             */
/*   Updated: 2023/08/22 16:29:37 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "color.h"

t_vec3	get_ray_dir(int pixel[2], t_viewport *vp)
{
	double	ndc_x;
	double	ndc_y;
	double	screen_x;
	double	screen_y;

	ndc_x = (2.0f * pixel[0]) / vp->w - 1.0f;
	ndc_y = 1.0f - (2.0f * pixel[1]) / vp->h;
	screen_x = ndc_x * vp->aspect_ratio * vp->focal;
	screen_y = ndc_y * vp->focal;
	return (normalize(new_vec3(
				screen_x,
				screen_y,
				-1.0f
			)));
}

double	get_closest_obj(t_ray ray, t_obj *obj, t_obj **closest, bool edit)
{
	t_obj	*tmp_obj;
	double	dist[2];

	tmp_obj = obj;
	dist[0] = INFINITY;
	while (tmp_obj)
	{
		if (tmp_obj->type == LIGHT && edit == false)
		{
			tmp_obj = tmp_obj->next;
			continue ;
		}
		dist[1] = tmp_obj->get_intersects(ray, tmp_obj);
		if (dist[1] != INFINITY && dist[1] < dist[0])
		{
			*closest = tmp_obj;
			dist[0] = dist[1];
		}
		tmp_obj = tmp_obj->next;
	}
	return (dist[0]);
}

void	fill_color(t_rgb color, t_viewport *vp, int pixel[2])
{
	unsigned char	*data;
	int				index;

	color = clamp(color, 0.0, 255.0);
	data = (unsigned char *) vp->img.data_addr;
	index = pixel[1] * vp->img.line_size + pixel[0] * (vp->img.bpp / 8);
	data[index] = (unsigned char) color.b;
	data[index + 1] = (unsigned char) color.g;
	data[index + 2] = (unsigned char) color.r;
}

static void	width_loop(int pixel[2], t_viewport *vp)
{
	double	t;
	t_ray	ray;
	t_obj	*closest;

	ray.origin = vp->scene->cam.pos;
	pixel[0] = 0;
	while (pixel[0] < (int) vp->w)
	{
		closest = NULL;
		ray.dir = get_ray_dir(pixel, vp);
		t = get_closest_obj(ray, vp->scene->obj, &closest, vp->edit);
		if (closest && !vp->edit)
		{
			if (closest->checkerboard)
				fill_color(checkerboard(vp, ray, closest, t), vp, pixel);
			else
				fill_color(phong_shading(vp, ray, closest, t), \
					vp, pixel);
		}
		else if (vp->edit && vp->selected && vp->selected == closest)
			fill_color(vp->selected->tmp_color, vp, pixel);
		else if (vp->edit)
			fill_color(edit_mode(vp, ray, closest, t), vp, pixel);
		pixel[0] += vp->edit * 2 + 1;
	}
}

void	render(t_viewport *vp)
{
	int		pixel[2];

	if (vp->edit)
		clean_img(vp);
	else
		printf("\n######## RENDERING ########\n");
	pixel[1] = 0;
	while (pixel[1] < (int) vp->h)
	{
		width_loop(pixel, vp);
		pixel[1] += vp->edit * 2 + 1;
	}
	mlx_put_image_to_window(vp->mlx, vp->win, vp->img.ptr, 0, 0);
	if (!vp->edit)
	{
		printf("DONE\n\n");
		printf("Press key SHIFT to enter EDIT MODE\n");
	}
}
