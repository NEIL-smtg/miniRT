/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:17:13 by mmuhamad          #+#    #+#             */
/*   Updated: 2023/08/22 13:42:16 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdlib.h>

void	get_stuff(t_viewport *vp, t_ray ray, t_obj *obj, t_stuff *stuff)
{
	double	diff;
	t_vec3	light_dir;

	stuff->surface_normal = get_surface_normal(ray, obj, stuff->t, vp->texture);
	stuff->inter = vec3_add(ray.origin, vec3_mul(stuff->t, ray.dir));
	light_dir = normalize(vec3_sub(stuff->sc.light->pos, stuff->inter));
	diff = vec3_dot(stuff->surface_normal, light_dir);
	stuff->diffuse = fmax(diff, 0);
	stuff->specular = get_specular_light(
			stuff->sc,
			stuff->surface_normal,
			stuff->inter, obj);
}

static void	init_g(t_tuv *g, t_obj *obj, t_stuff *stuff)
{
	g->ci = normalize(vec3_sub(stuff->inter, obj->center));
	g->r = obj->d / 2.0;
	g->h = obj->h;
	g->t_height = 10;
	g->t_width = 10;
}

t_rgb	checkerboard(t_viewport *vp, t_ray ray, t_obj *obj, double t)
{
	t_vec2	uv;
	t_stuff	stuff;
	t_tuv	g;
	t_rgb	final;

	stuff.t = t;
	stuff.sc = *vp->scene;
	final = new_rgb(0, 0, 0);
	while (stuff.sc.light)
	{
		get_stuff(vp, ray, obj, &stuff);
		init_g(&g, obj, &stuff);
		if (obj->checkerboard && obj->type == SPHERE)
			obj->get_uv(&g);
		stuff.color = checkerboard_extend(&stuff, obj, &g);
		stuff.amb = get_ambient_color(stuff.sc.amblight, stuff.color);
		if (in_shadows(stuff.sc, stuff.inter, obj, stuff.diffuse))
			final = rgb_add(get_ambient_color(stuff.sc.amblight,
						stuff.color), final);
		else
			final = rgb_add(final, rgb_add_3(stuff.amb,
						stuff.specular, rgb_scale(stuff.diffuse, stuff.color)));
		stuff.sc.light = stuff.sc.light->next;
	}
	return (final);
}
