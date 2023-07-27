/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:30:19 by mmuhamad          #+#    #+#             */
/*   Updated: 2023/07/27 12:44:32 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_rgb	get_selected_color(t_rgb c)
{
	double	min;
	double	max;

	min = fmin(c.r, c.g);
	min = fmin(min, c.b);
	max = fmax(c.r, c.g);
	max = fmax(max, c.b);
	if (min == c.r)
		c.r = max;
	else if (max == c.r)
		c.r = min;
	if (min == c.g)
		c.g = max;
	else if (max == c.g)
		c.g = min;
	if (min == c.b)
		c.b = max;
	else if (max == c.b)
		c.b = min;
	return (c);
}

void	render_edit(t_viewport *vp, t_scene sc)
{
	int		pixel[2];
	t_ray	ray;
	t_obj	*closest;
	double	t;

	if (vp->edit)
		clean_img(vp);
	ray.origin = sc.cam.pos;
	pixel[1] = 0;
	while (pixel[1] < (int) vp->h)
	{
		pixel[0] = 0;
		while (pixel[0] < (int) vp->w)
		{
			closest = NULL;
			ray.dir = get_ray_dir(pixel, vp, ray.origin);
			t = get_closest_obj(ray, sc.obj, &closest);
			if (vp->selected && vp->selected == closest)
				fill_color(vp->selected->tmp_color, vp, pixel);
			else if (closest)
				fill_color(closest->rgb, vp, pixel);
			pixel[0] += 3;
		}
		pixel[1] += 3;
	}
	mlx_put_image_to_window(vp->mlx, vp->win, vp->img.ptr, 0, 0);
}

void	selected_msg(t_obj *selected)
{
	if (selected->type == SPHERE)
		printf("\nSphere selected\n");
	else if (selected->type == PLANE)
		printf("\nPlane selected\n");
	else if (selected->type == CYLINDER)
		printf("\nCylinder selected\n");
	printf("Press:\n\tkey 7-0 for rotation\n");
	printf("\tWASD↑↓ for translation.\n");
	printf("\tcombination : h,+ to increase height\n");
	printf("\tcombination : h,- to increase height\n");
	printf("\tcombination : j,+ to increase diameter\n");
	printf("\tcombination : j,- to increase diameter\n");
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
	return (normalize(vec3_cross(normalize(vec3_cross(normalize(
							vp->selected->dir), new_vec3(0, 0, 1))),
				normalize(vp->selected->dir))));
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

int	mouse_event(int button, int x, int y, t_viewport *vp)
{
	int		pixel[2];
	t_ray	ray;

	printf("%d - %d\n", x, y);
	pixel[0] = x;
	pixel[1] = y;
	vp->selected = NULL;
	ray.dir = get_ray_dir(pixel, vp, ray.origin);
	get_closest_obj(ray, vp->scene->obj, &vp->selected);
	if (!vp->selected)
		return (0);
	vp->selected->edit_d = false;
	vp->selected->edit_h = false;
	vp->selected->tmp_color = get_selected_color(vp->selected->rgb);
	render_edit(vp, *vp->scene);
	selected_msg(vp->selected);
	return (0);
}

void	ft_edit(t_viewport *vp)
{
	if (vp->edit)
		return ;
	printf("EDIT MODE....\n");
	vp->edit = true;
	render_edit(vp, *vp->scene);
	mlx_mouse_hook(vp->win, mouse_event, vp);
}
