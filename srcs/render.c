/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 15:07:37 by suchua            #+#    #+#             */
/*   Updated: 2023/07/02 01:49:00 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "color.h"

t_vec3	get_ray_dir(int pixel[2], t_viewport *vp, t_vec3 cam_origin)
{
	t_vec3	pixel_coord;

	pixel_coord.x = (double) pixel[0] - vp->w / 2.0;
	pixel_coord.y = (double) pixel[1] - vp->h / 2.0;
	pixel_coord.z = vp->focal;
	return (normalize(pixel_coord));
}

t_rgb	get_closest_obj_color(t_ray ray, t_obj *obj)
{
	t_obj	*tmp_obj;
	double	dist[2];
	t_rgb	color;

	tmp_obj = obj;
	dist[0] = INFINITY;
	color = new_rgb(0, 0, 0);
	while (tmp_obj)
	{
		dist[1] = tmp_obj->get_intersects(ray, tmp_obj);
		if (dist[1] != INFINITY && dist[1] < dist[0])
		{
			color = tmp_obj->rgb;
			dist[0] = dist[1];
		}
		tmp_obj = tmp_obj->next;
	}
	return (color);
}

void	fill_color(t_rgb color, t_viewport *vp, int pixel[2])
{
	unsigned char	*data;
	int				index;

	data = (unsigned char *) vp->img.data_addr;
	index = (pixel[1] * vp->img.line_size + pixel[0] * (vp->img.bpp / 8));
	data[index] = (unsigned char) color.b;
	data[index + 1] = (unsigned char) color.g;
	data[index + 2] = (unsigned char) color.r;
}

void	render(t_viewport *vp, t_scene sc)
{
	int		pixel[2];
	t_ray	ray;
	t_rgb	color;

	printf("RENDERING....\n");
	ray.origin = sc.cam.pos;
	pixel[1] = -1;
	while (++pixel[1] < (int) vp->h)
	{
		pixel[0] = -1;
		while (++pixel[0] < (int) vp->w)
		{
			ray.dir = get_ray_dir(pixel, vp, ray.origin);
			color = get_closest_obj_color(ray, sc.obj);
			fill_color(color, vp, pixel);
		}
		printf("Progress : %.2f%%\n", (double) pixel[1] / vp->h * 100);
	}
	mlx_put_image_to_window(vp->mlx, vp->win, vp->img.ptr, 0, 0);
	printf("DONE\n");
}
