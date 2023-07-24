/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:30:19 by mmuhamad          #+#    #+#             */
/*   Updated: 2023/07/24 19:09:45 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_user_command(void)
{
	char	*comm;

	printf("TYPE AN ELEMENT TO EDIT : ");
	comm = get_next_line(0);
	if (!ft_strncmp(comm, "sp", 2))
		return(1);
	return (0);
}

static t_vec3	get_ray_dir(int pixel[2], t_viewport *vp, t_vec3 cam_origin)
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

static double	get_closest_obj(t_ray ray, t_obj *obj, t_obj **closest)
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

static void	fill_color(t_rgb color, t_viewport *vp, int pixel[2])
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

void	render_edit(t_viewport *vp, t_scene sc)
{
	int		pixel[2];
	t_ray	ray;
	t_obj	*closest;
	double	t;

	printf("EDIT MODE....\n");
	clean_img(vp);
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
				fill_color(closest->rgb, vp, pixel);
		}
	}
	mlx_put_image_to_window(vp->mlx, vp->win, vp->img.ptr, 0, 0);
	// printf("EXIT EDITING MODE\n");
}

int	mouse_event(int button, int x, int y, t_viewport *vp)
{
	int		pixel[2];
	t_ray	ray;
	t_rgb	cp;
	t_obj	*closest;

	pixel[0] = x;
	pixel[1] = y;
	ray.origin = vp->scene->cam.pos;
	closest = NULL;
	ray.dir = get_ray_dir(pixel, vp, ray.origin);
	double t = get_closest_obj(ray, vp->scene->obj, &closest);
	printf("t = %f\n", t);
	if (closest)
	{
		cp = new_rgb(closest->rgb.r, closest->rgb.g, closest->rgb.b);
		closest->rgb.r = 255;
		closest->rgb.g = 0;
		closest->rgb.b = 0;
		closest->d += 1;
	}
	render_edit(vp, *vp->scene);
	return(0);
}

void	ft_edit(t_viewport *vp)
{
	int		type;

	vp->edit = true;
	render_edit(vp, *vp->scene);
	mlx_mouse_hook(vp->win, mouse_event, vp);
}
