/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:28:09 by suchua            #+#    #+#             */
/*   Updated: 2023/08/22 16:53:42 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_rgb(t_rgb rgb)
{
	printf("\trgb : %f, %f, %f\n}\n\n",
		rgb.r, rgb.g, rgb.b);
}

static void	print_vec(t_vec3 v, int type)
{
	if (type == 1)
		printf("\tposition : %f, %f, %f\n", v.x, v.y, v.z);
	else
		printf("\tdirection : %f, %f, %f\n", v.x, v.y, v.z);
}

static void	print_setting(t_scene *sc)
{
	t_light	*lg;

	printf("############## Settings ##############\n");
	printf("Ambient Light\t{\n");
	printf("\tLightning ratio : %f\n", sc->amblight.ratio);
	print_rgb(sc->amblight.rgb);
	lg = sc->light;
	while (lg)
	{
		printf("Light\t{\n");
		print_vec(lg->pos, 1);
		printf("\tbrightness : %f\n", lg->brightness);
		print_rgb(lg->rgb);
		lg = lg->next;
	}
	printf("Camera\t{\n");
	print_vec(sc->cam.pos, 1);
	print_vec(sc->cam.dir, 2);
	printf("\tfov : %f rad\n}\n\n", sc->cam.fov);
}

void	print_scene(t_scene *sc)
{
	t_obj	*tmp;

	print_setting(sc);
	printf("############## Shapes ##############\n");
	tmp = sc->obj;
	while (tmp)
	{
		print_obj(tmp);
		print_vec(tmp->center, 1);
		if (tmp->type != SPHERE && tmp->type != LIGHT)
			print_vec(tmp->dir, 2);
		if (tmp->type != PLANE && tmp->type != LIGHT)
			printf("\tdiameter : %f\n", tmp->d);
		if (tmp->type == CYLINDER || tmp->type == CONE)
			printf("\theight : %f\n", tmp->h);
		if (tmp->type == CONE)
			printf("\tangle : %f\n", tmp->cone_angle);
		print_rgb(tmp->rgb);
		tmp = tmp->next;
	}
}

void	print_mat4(t_mat4 mat)
{
	t_vec4	r1;
	t_vec4	r2;
	t_vec4	r3;
	t_vec4	r4;

	r1 = mat.r1;
	r2 = mat.r2;
	r3 = mat.r3;
	r4 = mat.r4;
	printf("row 1 = %f, %f, %f, %f\n", r1.x, r1.y, r1.z, r1.w);
	printf("row 2 = %f, %f, %f, %f\n", r2.x, r2.y, r2.z, r2.w);
	printf("row 3 = %f, %f, %f, %f\n", r3.x, r3.y, r3.z, r3.w);
	printf("row 4 = %f, %f, %f, %f\n", r4.x, r4.y, r4.z, r4.w);
}
