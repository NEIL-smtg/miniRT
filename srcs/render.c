/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 15:07:37 by suchua            #+#    #+#             */
/*   Updated: 2023/07/11 19:23:33 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "color.h"

t_vec3	get_ray_dir(int pixel[2], t_viewport *vp, t_vec3 cam_origin)
{
	// double	ndc_x;
	// double	ndc_y;
	// double	screen_x;
	// double	screen_y;
	
	// ndc_x = (2.0f * pixel[0]) / vp->w - 1.0f;
	// ndc_y = 1.0f - (2.0f * pixel[1]) / vp->h;
	// screen_x = ndc_x * vp->aspect_ratio * vp->focal;
	// screen_y = ndc_y * vp->focal;
	// return (normalize(new_vec3(
	// 		screen_x,
	// 		screen_y,
	// 		-1.0f
	// 	)));

	double	u,v;
	t_vec3	raydir, tmp, screen_pt;

	u = (double) pixel[0] / vp->w;
	v = (double) pixel[1] / vp->h;
	screen_pt = vec3_mul(u, vec3_sub(vp->p1, vp->p0));
	screen_pt = vec3_add(screen_pt, vp->p0);
	screen_pt = vec3_add(screen_pt , vec3_mul(v, vec3_sub(vp->p2, vp->p0)));
	raydir = vec3_sub(screen_pt, cam_origin);
	// tmp = vec3_add(new_vec3(u * vp->w, 0, 0), new_vec3(0, v * vp->h, 0));
	// raydir = vec3_add(vp->lowerleft, vec3_sub(tmp, cam_origin));
	return (normalize(raydir));
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
		// printf("Progress : %.2f%%\n", (double) pixel[1] / vp->h * 100);
	}
	mlx_put_image_to_window(vp->mlx, vp->win, vp->img.ptr, 0, 0);
	printf("DONE\n");
}
