/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:47:56 by suchua            #+#    #+#             */
/*   Updated: 2023/08/14 02:40:27 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "color.h"

typedef struct s_th
{
	t_viewport	*vp;
	int			start_y;
	int			end_y;
}	t_th;

typedef struct s_render
{
	pthread_t	th[THREAD_NUM];
	t_th		data[THREAD_NUM];
	int			lines_per_thread;
	int			remaining_lines;
}	t_render;

t_vec3	get_ray_dir(int pixel[2], t_viewport *vp, t_vec3 cam_origin)
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

t_vec3	get_ray_dir_offset(int pixel[2], t_viewport *vp, t_vec3 cam_origin, \
	double offset[2])
{
	double	ndc_x;
	double	ndc_y;
	double	screen_x;
	double	screen_y;

	ndc_x = (2.0f * ((double) pixel[0] + offset[0])) / vp->w - 1.0f;
	ndc_y = 1.0f - (2.0f * ((double) pixel[1] + offset[1])) / vp->h;
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

void	anti_aliasing(int pixel[2], t_viewport *vp)
{
	const double	sample_step = 1.0 / 4.0;
	double			offset[2];
	double			t;
	t_ray			ray;
	t_obj			*closest;
	t_rgb			final;

	ray.origin = vp->scene->cam.pos;
	final = new_rgb(0, 0 , 0);
	offset[1] = 0;
	while (offset[1] < 1.0)
	{
		offset[0] = 0;
		while (offset[0] < 1.0)
		{
			closest = NULL;
			ray.dir = get_ray_dir_offset(pixel, vp, ray.origin, offset);
			t = get_closest_obj(ray, vp->scene->obj, &closest, vp->edit);
			if (closest)
			{
				if (closest->checkerboard)
					final = rgb_add(final, checkerboard(vp, ray, closest, t));
				else
					final = rgb_add(final, phong_shading(vp, ray, closest, t));
			}
			offset[0] += sample_step;
		}
		offset[1] += sample_step;
	}
	fill_color(rgb_scale(pow(sample_step, 2), final), vp, pixel);
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
		if (!vp->edit)
		{
			anti_aliasing(pixel, vp);
			pixel[0] += vp->edit * 2 + 1;
			continue ;
		}
		closest = NULL;
		ray.dir = get_ray_dir(pixel, vp, ray.origin);
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

void	*render_thread(void *arg)
{
	t_th	*data;
	int		pixel[2];

	data = (t_th *) arg;
	pixel[1] = data->start_y;
	while (pixel[1] < data->end_y)
	{
		width_loop(pixel, data->vp);
		pixel[1] += data->vp->edit * 2 + 1;
	}
	return (NULL);
}

void	thread_runner(t_viewport *vp)
{
	int			i;
	int			start_y;
	t_render	r;

	r.lines_per_thread = (int) vp->h / THREAD_NUM;
	r.remaining_lines = (int) vp->h % THREAD_NUM;
	i = -1;
	start_y = 0;
	while (++i < THREAD_NUM)
	{
		r.data[i].vp = vp;
		r.data[i].start_y = start_y;
		r.data[i].end_y = start_y + r.lines_per_thread;
		if (r.remaining_lines > 0)
		{
			r.data[i].end_y++;
			r.remaining_lines--;
		}
		pthread_create(&r.th[i], NULL, render_thread, &r.data[i]);
		start_y = r.data[i].end_y;
	}
	i = -1;
	while (++i < THREAD_NUM)
		pthread_join(r.th[i], NULL);
}

void	render(t_viewport *vp)
{
	int			i;
	t_th		data;

	if (vp->edit)
	{
		clean_img(vp);
		data.start_y = 0;
		data.end_y = (int) vp->h;
		data.vp = vp;
		render_thread(&data);
	}
	else
	{
		printf("\n######## RENDERING ########\n");
		thread_runner(vp);
	}
	mlx_put_image_to_window(vp->mlx, vp->win, vp->img.ptr, 0, 0);
	if (!vp->edit)
	{
		printf("DONE\n\n");
		printf("Press key SHIFT to enter EDIT MODE\n");
	}
}
