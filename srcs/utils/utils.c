/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 02:03:41 by suchua            #+#    #+#             */
/*   Updated: 2023/07/11 19:06:24 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_rgb(t_rgb rgb)
{
	printf("\trgb : %d, %d, %d\n}\n\n",
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
	printf("############## Settings ##############\n");
	printf("Ambient Light\t{\n");
	printf("\tLightning ratio : %f\n", sc->amblight.ratio);
	print_rgb(sc->amblight.rgb);
	printf("Light\t{\n");
	print_vec(sc->light.pos, 1);
	printf("\tbrightness : %f\n", sc->light.brightness);
	print_rgb(sc->light.rgb);
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
		if (tmp->type == SPHERE)
			printf("SPHERE\t{\n");
		else if (tmp->type == PLANE)
			printf("PLANE\t{\n");
		else
			printf("CYLINDER\t{\n");
		print_vec(tmp->center, 1);
		if (tmp->type != SPHERE)
			print_vec(tmp->dir, 2);
		if (tmp->type != PLANE)
			printf("\tdiameter : %f\n", tmp->d);
		if (tmp->type == CYLINDER)
			printf("\theight : %f\n", tmp->h);
		print_rgb(tmp->rgb);
		tmp = tmp->next;
	}
}

//	calculate focal length
double	get_focal_length(double rad, double width)
{
	return ((width / 2) / tan(rad / 2));
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
