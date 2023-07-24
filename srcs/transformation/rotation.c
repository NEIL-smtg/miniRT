/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 01:43:56 by suchua            #+#    #+#             */
/*   Updated: 2023/07/24 20:46:05 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "minirt.h"

void	origin_translation(t_scene *sc, t_vec3 rot_center, enum e_rotation rot)
{
	t_vec3	translate;
	t_obj	*tmp;

	translate = rot_center;
	if (rot == to_origin)
		translate = vec3_mul(-1, rot_center);
	tmp = sc->obj;
	while (tmp)
	{
		tmp->center = vec3_add(tmp->center, translate);
		tmp = tmp->next;
	}
	sc->cam.pos = vec3_add(sc->cam.pos, translate);
	sc->light.pos = vec3_add(sc->light.pos, translate);
}

t_vec3	get_cam_right(t_mat4 view_mat)
{
	view_mat = mat4_transposition(view_mat);
	return (vec3_from_vec4(view_mat.r1));
}

t_vec3	get_cam_up(t_mat4 view_mat)
{
	view_mat = mat4_transposition(view_mat);
	return (vec3_from_vec4(view_mat.r2));
}

t_vec3	get_cam_forward(t_mat4 view_mat)
{
	view_mat = mat4_transposition(view_mat);
	return (vec3_from_vec4(view_mat.r3));
}
