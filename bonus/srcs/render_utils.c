/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:24:15 by mmuhamad          #+#    #+#             */
/*   Updated: 2023/08/16 17:27:03 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

void	anti_aliasing(int pixel[2], t_viewport *vp)
{
	const double	sample_step = 1.0 / 4.0;
	double			offset[2];
	double			t;
	t_ray			ray;
	t_obj			*closest;
	t_rgb			final;

	ray.origin = vp->scene->cam.pos;
	final = new_rgb(0, 0, 0);
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
