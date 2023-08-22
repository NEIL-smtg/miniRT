/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 00:01:04 by suchua            #+#    #+#             */
/*   Updated: 2023/08/22 16:56:53 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	get_ray_dir_offset(int pixel[2], t_viewport *vp, \
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

static t_rgb	pixel_color(t_viewport *vp, t_ray ray,
	t_obj *closest, double t)
{
	if (closest && closest->checkerboard)
		return (checkerboard(vp, ray, closest, t));
	else if (closest)
		return (phong_shading(vp, ray, closest, t));
	return (new_rgb(0, 0, 0));
}

void	anti_aliasing(int pixel[2], t_viewport *vp, int *x)
{
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
			ray.dir = get_ray_dir_offset(pixel, vp, offset);
			t = get_closest_obj(ray, vp->scene->obj, &closest, vp->edit);
			final = rgb_add(final, pixel_color(vp, ray, closest, t));
			offset[0] += 1.0 / SAMPLE_STEP;
		}
		offset[1] += 1.0 / SAMPLE_STEP;
	}
	fill_color(rgb_scale(pow(1.0 / SAMPLE_STEP, 2), final), vp, pixel);
	*x += vp->edit * 2 + 1;
}
