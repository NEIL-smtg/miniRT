/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 00:44:15 by suchua            #+#    #+#             */
/*   Updated: 2023/06/05 21:01:43 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_viewport(t_viewport *vp, t_camera cam)
{
	vp->aspect_ratio = 16.0 / 9.0;
	vp->h = HEIGHT;
	vp->w = HEIGHT * vp->aspect_ratio;
	vp->origin = cam.pos;
	vp->focal = get_focal_length(cam.fov, vp->w);
	vp->transform = get_transformation_mat(cam.vec);
}

void	set_camera_view(t_mat transform, t_scene *sc)
{
	t_obj	*tmp;

	sc->light.pos = mat_transform(transform, sc->light.pos);
	sc->cam.pos = mat_transform(transform, sc->cam.pos);
	sc->cam.vec = mat_transform(transform, sc->cam.vec);
	tmp = sc->obj;
	while (tmp)
	{
		tmp->center = mat_transform(transform, tmp->center);
		if (tmp->type != SPHERE)
			tmp->dir = mat_transform(transform, tmp->dir);
		tmp = tmp->next;
	}
}

int	main(int ac, char **av)
{
	t_scene		scene;
	t_viewport	vp;

	if (!valid_arg(ac, av))
		return (1);
	get_input(av[1], &scene);
	init_viewport(&vp, scene.cam);
	set_camera_view(vp.transform, &scene);
	print_scene(&scene);
	return (0);
}
