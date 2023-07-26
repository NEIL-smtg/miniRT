/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:30:19 by mmuhamad          #+#    #+#             */
/*   Updated: 2023/07/26 16:29:06 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_user_command(void)
{
	char	*comm;

	printf("TYPE AN ELEMENT TO EDIT : ");
	comm = get_next_line(0);
	if (!ft_strncmp(comm, "sp", 2))
		return (1);
	return (0);
}

void	render_edit(t_viewport *vp, t_scene sc)
{
	int		pixel[2];
	t_ray	ray;
	t_obj	*closest;
	double	t;

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
			{
				fill_color(closest->rgb, vp, pixel);
			}
		}
	}
	mlx_put_image_to_window(vp->mlx, vp->win, vp->img.ptr, 0, 0);
	// printf("EXIT EDITING MODE\n");
}

int	mouse_event(int button, int x, int y, t_viewport *vp)
{
	int		pixel[2];
	t_ray	ray;
	double	t;
	t_rgb	cp;

	printf("%d %d\n", x, y);
	pixel[0] = x;
	pixel[1] = y;
	ray.origin = vp->scene->cam.pos;
	vp->selected = NULL;
	ray.dir = get_ray_dir(pixel, vp, ray.origin);

	/*
		build a sorted list of object with respect of t
		user can pick any object in this ray instead of the closest only
		only diameter, height, width needed to be modifed
	*/

	t = get_closest_obj(ray, vp->scene->obj, &vp->selected);
	if (vp->selected)
	{
		cp = vp->selected->rgb;
		vp->selected->rgb = new_rgb(255, 0, 0);
	}
	render_edit(vp, *vp->scene);
	if (vp->selected)
		vp->selected->rgb = cp;
	return (0);
}

void	ft_edit(t_viewport *vp)
{
	int		type;

	printf("EDIT MODE....\n");
	vp->edit = true;
	render_edit(vp, *vp->scene);
	mlx_mouse_hook(vp->win, mouse_event, vp);
}
