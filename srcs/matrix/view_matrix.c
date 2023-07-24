/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 02:12:48 by suchua            #+#    #+#             */
/*   Updated: 2023/07/24 13:44:06 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mat4	get_view_matrix(t_camera cam)
{
	t_vec3	right;
	t_vec3	forward;
	t_vec3	up;
	t_mat4	view_mat;

	forward = normalize(cam.dir);
	if (forward.y == 1)
		right = normalize(vec3_cross(forward, new_vec3(0, 0, 1)));
	else
		right = normalize(vec3_cross(forward, new_vec3(0, 1, 0)));				
	up = normalize(vec3_cross(right, forward));
	right = normalize(vec3_cross(up, forward));
	view_mat.r1 = vec4_from_vec3(right, 0.0f);
	view_mat.r2 = vec4_from_vec3(up, 0.0f);
	view_mat.r3 = vec4_from_vec3(vec3_mul(-1.0f, forward), 0.0f);
	view_mat.r4 = new_vec4(
			-vec3_dot(right, cam.pos),
			-vec3_dot(up, cam.pos),
			-vec3_dot(forward, cam.pos) * -1.0f,
			1.0f
			);
	return (mat4_transposition(view_mat));
}

t_vec3	convert_to_view_space(t_mat4 view_mat, t_vec3 v)
{
	t_vec4	p;
	t_vec4	after;
	t_vec3	res;

	p = vec4_from_vec3(v, 1.0f);
	after = mat44_mul_mat41(view_mat, p);
	res = vec3_from_vec4(after);
	if (after.w == 0.0f)
		return (res);
	return (vec3_mul(1 / after.w, res));
}

void	world_to_camera(t_mat4 inv_view_mat, t_scene *sc)
{
	t_obj	*tmp;

	sc->cam.pos = convert_to_view_space(inv_view_mat, sc->cam.pos);
	sc->cam.dir = normalize(convert_to_view_space(inv_view_mat, sc->cam.dir));
	sc->light.pos = convert_to_view_space(inv_view_mat, sc->light.pos);
	tmp = sc->obj;
	while (tmp)
	{
		tmp->center = convert_to_view_space(inv_view_mat, tmp->center);
		if (tmp->type != SPHERE)
			tmp->dir = normalize(convert_to_view_space(inv_view_mat, tmp->dir));
		tmp = tmp->next;
	}
}

void	rotation_transformation(t_mat4 inv_view_mat, t_scene *sc)
{
	t_obj	*tmp;

	// sc->cam.pos = convert_to_view_space(inv_view_mat, sc->cam.pos);
	// sc->cam.dir = normalize(convert_to_view_space(inv_view_mat, sc->cam.dir));
	sc->light.pos = convert_to_view_space(inv_view_mat, sc->light.pos);
	tmp = sc->obj;
	while (tmp)
	{
		tmp->center = convert_to_view_space(inv_view_mat, tmp->center);
		if (tmp->type != SPHERE)
			tmp->dir = normalize(convert_to_view_space(inv_view_mat, tmp->dir));
		tmp = tmp->next;
	}
}
