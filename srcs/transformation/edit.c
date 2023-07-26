/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:30:19 by mmuhamad          #+#    #+#             */
/*   Updated: 2023/07/26 19:24:10 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

void	origin_translate(t_vec3 rot_center,
		enum e_rotation rot, t_viewport *vp)
{
	t_vec3	translate;
	t_obj	*obj;

	translate = rot_center;
	if (rot == to_origin)
	{
		translate = vec3_mul(-1, rot_center);
	}
	if (vp->selected)
	{
		vp->selected->center = vec3_add(vp->selected->center, translate);
	}
}

void	quaternion_rotation(t_quat q, t_viewport *vp)
{
	vp->selected->center = rotate(vp->selected->center, q);
	if (vp->selected->type != SPHERE)
		vp->selected->dir = normalize(rotate(vp->selected->dir, q));
}

t_vec3	get_rot_axis(int keycode, t_viewport *vp, int *angle)
{
	if (keycode == KEY_SEVEN || keycode == KEY_NINE)
		*angle = -ANGLE_ROTATION;
	else
		*angle = ANGLE_ROTATION;
	if (keycode == KEY_SEVEN || keycode == KEY_EIGHT)
	{
		return (normalize(vec3_cross(vp->selected->dir, new_vec3(0, 0, 1))));
	}
	else if (keycode == KEY_NINE || keycode == KEY_ZERO)
	{
		return (normalize(vec3_cross(normalize(vec3_cross(
							normalize(vp->selected->dir), new_vec3(0, 0, 1))),
					normalize(vp->selected->dir))));
	}
	return (normalize(vec3_cross(normalize(vec3_cross(normalize(vp->selected->dir), new_vec3(0, 0, 1))), normalize(vp->selected->dir))));
}

void	ft_obj_panning(int keycode, t_viewport *vp)
{
	t_quat	q;
	t_vec3	rot_center;
	t_vec3	rot_axis;
	int		angle;

	rot_axis = get_rot_axis(keycode, vp, &angle);
	rot_center = vp->selected->center;
	origin_translate(rot_center, to_origin, vp);
	q = get_quaternion(get_radian(angle), rot_axis);
	quaternion_rotation(q, vp);
	origin_translate(rot_center, revert, vp);
	render_edit(vp, *vp->scene);
}

// int	obj_rot(int keycode, t_viewport *vp)
// {
// 	if (keycode == KEY_THREE || keycode == KEY_FOUR
// 		|| keycode == KEY_FIVE || keycode == KEY_SIX)
// 		ft_obj_panning(keycode, vp);
// 	else if (keycode == KEY_R)
// 	{
// 		return (0);
// 	}
// 	return (0);
// }

int	mouse_event(int button, int x, int y, t_viewport *vp)
{
	int		pixel[2];
	t_ray	ray;
	double	t;
	t_rgb	cp;

	// printf("%d %d\n", x, y);
	pixel[0] = x;
	pixel[1] = y;
	ray.origin = vp->scene->cam.pos;
	vp->selected = NULL;
	ray.dir = get_ray_dir(pixel, vp, ray.origin);
	/*
		build a sorted list of object with respect of t
		user can pick any object in this ray instead of the closest only
		only diameter, height needed to be modifed
	*/
	t = get_closest_obj(ray, vp->scene->obj, &vp->selected);
	if (vp->selected)
	{
		cp = vp->selected->rgb;
		vp->selected->rgb = new_rgb(255, 0, 0);
	}
	render_edit(vp, *vp->scene);
	if (vp->selected)
		vp->selected->rgb = new_rgb(cp.r, cp.g, cp.b);
	// continue-code-here
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
