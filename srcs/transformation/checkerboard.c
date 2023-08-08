/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:17:13 by mmuhamad          #+#    #+#             */
/*   Updated: 2023/08/09 00:19:50 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdlib.h>

typedef struct s_vec2
{
	double	u;
	double	v;
}	t_vec2;

typedef struct s_stuff
{
	t_vec3	inter;
	double	t;
	t_vec3	surface_normal;
	double	diffuse;
	t_rgb	specular;
	t_rgb	color;
	t_rgb	amb;
}	t_stuff;

static t_rgb	get_amb_color(t_scene sc, t_rgb	color)
{
	t_rgb	amb;

	amb = new_rgb((color.r + sc.amblight.rgb.r) * 0.15,
			(color.g + sc.amblight.rgb.g) * 0.15,
			(color.b + sc.amblight.rgb.b) * 0.15);
	amb = rgb_scale(sc.amblight.ratio, amb);
	return (amb);
}

void	get_uv_square(int *u_square, int *v_square, t_vec2	*uv, t_obj *obj)
{
	double	square_size;

	if (obj->type == SPHERE || obj->type == CYLINDER || obj->type == CONE)
	{
		square_size = 0.2f;
		*u_square = floor(uv->u / square_size);
		*v_square = floor(uv->v / square_size);
	}
	else if (obj->type == PLANE)
	{
		square_size = EPS;
		*u_square = floor(uv->u * square_size);
		*v_square = floor(uv->v * square_size);
	}
}

t_rgb	checkerboard_color(float u, float v, t_obj *obj)
{
	double	square_size;
	int		u_square;
	int		v_square;
	t_vec2	uv;

	uv.u = u;
	uv.v = v;
	get_uv_square(&u_square, &v_square, &uv, obj);
	if (((u_square + v_square) % 2) == 0)
	{
		return (new_rgb(255, 255, 255));
	}
	return (new_rgb(50, 50, 50));
}

void	get_stuff(t_viewport *vp, t_ray ray, t_obj *obj, t_stuff *stuff)
{
	stuff->surface_normal = get_surface_normal(ray, obj, stuff->t, vp->texture);
	stuff->inter = vec3_add(ray.origin, vec3_mul(stuff->t, ray.dir));
	stuff->diffuse = get_diffuse_color(vp->scene->light, stuff->inter,
			stuff->surface_normal);
	stuff->specular = get_specular_light(*vp->scene, stuff->surface_normal,
			stuff->inter, obj);
}

t_rgb	checkerboard(t_viewport *vp, t_ray ray, t_obj *obj, double t)
{
	t_vec2	uv;
	t_stuff	stuff;

	stuff.t = t;
	get_stuff(vp, ray, obj, &stuff);
	if (obj->checkerboard && obj->type == SPHERE)
	{
		get_sphere_uv(&stuff.inter, &uv.u, &uv.v, obj);
		stuff.color = checkerboard_color(uv.u, uv.v, obj);
		stuff.amb = get_amb_color(*vp->scene, stuff.color);
		if (in_shadows(*vp->scene, stuff.inter, obj, stuff.diffuse))
			return (new_rgb(stuff.amb.r, stuff.amb.g, stuff.amb.b));
		return (new_rgb(
				stuff.amb.r + stuff.specular.r + (stuff.color.r * stuff.diffuse),
				stuff.amb.g + stuff.specular.g + (stuff.color.g * stuff.diffuse),
				stuff.amb.b + stuff.specular.b + (stuff.color.b * stuff.diffuse)));
	}
	else if (obj->checkerboard && obj->type == PLANE)
	{
		get_plane_uv(&stuff.inter, &uv.u, &uv.v, obj);
		stuff.color = checkerboard_color(uv.u, uv.v, obj);
		stuff.amb = get_amb_color(*vp->scene, stuff.color);
		if (in_shadows(*vp->scene, stuff.inter, obj, stuff.diffuse))
			return (new_rgb(stuff.amb.r, stuff.amb.g, stuff.amb.b));
		return (new_rgb(
				stuff.amb.r + stuff.specular.r + (stuff.color.r * stuff.diffuse),
				stuff.amb.g + stuff.specular.g + (stuff.color.g * stuff.diffuse),
				stuff.amb.b + stuff.specular.b + (stuff.color.b * stuff.diffuse)));
	}
	else if (obj->checkerboard && obj->type == CYLINDER)
	{
		get_cylinder_uv(&stuff.inter, &uv.u, &uv.v, obj);
		stuff.color = checkerboard_color(uv.u, uv.v, obj);
		stuff.amb = get_amb_color(*vp->scene, stuff.color);
		if (in_shadows(*vp->scene, stuff.inter, obj, stuff.diffuse))
			return (new_rgb(stuff.amb.r, stuff.amb.g, stuff.amb.b));
		return (new_rgb(
				stuff.amb.r + stuff.specular.r + (stuff.color.r * stuff.diffuse),
				stuff.amb.g + stuff.specular.g + (stuff.color.g * stuff.diffuse),
				stuff.amb.b + stuff.specular.b + (stuff.color.b * stuff.diffuse)));
	}
	else if (obj->checkerboard && obj->type == CONE)
	{
		get_sphere_uv(&stuff.inter, &uv.u, &uv.v, obj);
		stuff.color = checkerboard_color(uv.u, uv.v, obj);
		stuff.amb = get_amb_color(*vp->scene, stuff.color);
		if (in_shadows(*vp->scene, stuff.inter, obj, stuff.diffuse))
			return (new_rgb(stuff.amb.r, stuff.amb.g, stuff.amb.b));
		return (new_rgb(
				stuff.amb.r + stuff.specular.r + (stuff.color.r * stuff.diffuse),
				stuff.amb.g + stuff.specular.g + (stuff.color.g * stuff.diffuse),
				stuff.amb.b + stuff.specular.b + (stuff.color.b * stuff.diffuse)));
	}
	return (new_rgb(255, 255, 255));
}
