/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 15:07:37 by suchua            #+#    #+#             */
/*   Updated: 2023/07/24 14:07:05 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "color.h"

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

	// double	u,v;
	// t_vec3	raydir, tmp, screen_pt;

	// u = (double) pixel[0] / vp->w;
	// v = (double) pixel[1] / vp->h;
	// screen_pt = vec3_mul(u, vec3_sub(vp->p1, vp->p0));
	// screen_pt = vec3_add(screen_pt, vp->p0);
	// screen_pt = vec3_add(screen_pt , vec3_mul(v, vec3_sub(vp->p2, vp->p0)));
	// raydir = vec3_sub(screen_pt, cam_origin);
	// return (normalize(raydir));
}

double	get_closest_obj(t_ray ray, t_obj *obj, t_obj **closest)
{
	t_obj	*tmp_obj;
	double	dist[2];

	tmp_obj = obj;
	dist[0] = INFINITY;
	while (tmp_obj)
	{
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

	color = clamp(color, 0.0f, 255.0f);
	data = (unsigned char *) vp->img.data_addr;
	index = pixel[1] * vp->img.line_size + pixel[0] * (vp->img.bpp / 8);
	data[index] = (unsigned char) color.b;
	data[index + 1] = (unsigned char) color.g;
	data[index + 2] = (unsigned char) color.r;
}

void	render(t_viewport *vp, t_scene sc)
{
	int		pixel[2];
	t_ray	ray;
	t_obj	*closest;
	double	t;

	printf("RENDERING....\n");
	ray.origin = sc.cam.pos;
	pixel[1] = -1;
	while (++pixel[1] < (int) vp->h)
	{
		pixel[0] = -1;
		while (++pixel[0] < (int) vp->w)
		{
			closest = NULL;
			ray.dir = get_ray_dir(pixel, vp, ray.origin);
			t = get_closest_obj(ray, sc.obj, &closest);
			if (closest)
				fill_color(phong_shading(sc, ray, closest, t), vp, pixel);
			// else
			// 	fill_color(rgb_scale(sc.amblight.ratio, sc.amblight.rgb), vp, pixel);
		}
	}
	mlx_put_image_to_window(vp->mlx, vp->win, vp->img.ptr, 0, 0);
	printf("DONE\n");
}
