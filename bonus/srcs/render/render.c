/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:47:56 by suchua            #+#    #+#             */
/*   Updated: 2024/07/13 21:04:33 by suchua           ###   ########.fr       */
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
	while (pixel[0] < (int) vp->w)
	{
		// if (!vp->edit)
		// {
		// 	anti_aliasing(pixel, vp, &pixel[0]);
		// 	continue ;
		// }
		closest = NULL;
		ray.dir = get_ray_dir(pixel, vp);
		t = get_closest_obj(ray, vp->scene->obj, &closest, vp->edit);
		if (closest && !vp->edit && closest->checkerboard)
			fill_color(checkerboard(vp, ray, closest, t), vp, pixel);
		else if (closest && !vp->edit)
			fill_color(phong_shading(vp, ray, closest, t), vp, pixel);
		else if (vp->edit && vp->selected && vp->selected == closest)
			fill_color(vp->selected->tmp_color, vp, pixel);
		else if (vp->edit)
			fill_color(edit_mode(vp, ray, closest, t), vp, pixel);
		pixel[0] += vp->edit * 2 + 1;
	}
}

void	*routine(void *arg)
{
	t_th	*data;
	int		pixel[2];

	data = (t_th *) arg;
	pixel[1] = data->start_y;
	while (pixel[1] < data->end_y)
	{
		pixel[0] = 0;
		width_loop(pixel, data->vp);
		pixel[1] += data->vp->edit * 2 + 1;
	}
	return (NULL);
}
