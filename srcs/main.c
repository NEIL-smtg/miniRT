/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 00:44:15 by suchua            #+#    #+#             */
/*   Updated: 2023/06/27 02:52:25 by suchua           ###   ########.fr       */
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
	vp->transform = get_transformation_mat(cam.dir);
}

void	set_camera_view(t_mat3 transform, t_scene *sc)
{
	t_obj	*tmp;

	sc->light.pos = mat_transform(transform, sc->light.pos);
	sc->cam.pos = mat_transform(transform, sc->cam.pos);
	sc->cam.dir = mat_transform(transform, sc->cam.dir);
	tmp = sc->obj;
	while (tmp)
	{
		tmp->center = mat_transform(transform, tmp->center);
		if (tmp->type != SPHERE)
			tmp->dir = mat_transform(transform, tmp->dir);
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

t_mat4	get_proj_matrix(t_viewport vp)
{
	double	near;
	double	far;
	double	frustrum_depth;

	near = 0.1f;
	far = 100.0f;
	frustrum_depth = far - near;
	return (
		new_mat4(
			new_vec4(1.0f / (vp.aspect_ratio * vp.focal), 0, 0, 0),
			new_vec4(0, 1.0f / vp.focal, 0, 0),
			new_vec4(0, 0, -(far + near) / frustrum_depth, -1.0f),
			new_vec4(0, 0, -(2.0f * far * near) / frustrum_depth, 0)
		)	
	);
}

t_mat4	get_view_matrix(t_camera cam)
{
	t_vec3	right;
	t_vec3	up;
	t_vec3	forward;

	forward = normalize(new_vec3(-cam.dir.x, -cam.dir.y, -cam.dir.z));
	up = new_vec3(0, 1, 0);
	right = normalize(vec3_cross(up, forward));
	up = vec3_cross(forward, right);
	return (new_mat4(
		new_vec4(right.x, up.x, forward.x, -vec3_dot(right, cam.pos)),
		new_vec4(right.y, up.y, forward.y, -vec3_dot(up, cam.pos)),
		new_vec4(right.z, up.z, forward.z, -vec3_dot(forward, cam.pos)),
		new_vec4(0, 0, 0, 1)
	));
}

void	convert_to_cam_view(t_mat4 view_mat, t_scene *sc)
{
	t_obj	*tmp;
	t_vec4	tmp_c;
	t_vec4	tmp_n;

	tmp = sc->obj;
	while (tmp)
	{
		tmp_c = convert_to_4d(tmp->center);
		if (tmp->type != SPHERE)
			tmp_n = convert_to_4d(tmp->dir);
		tmp->center = convert_to_3d(mat4_mul(view_mat, tmp_c));
		if (tmp->type != SPHERE)
			tmp->dir = convert_to_3d(mat4_mul(view_mat, tmp_n));
		tmp = tmp->next;
	}
}

void	render(t_viewport vp, t_scene sc)
{
	int	pixel[2];

	pixel[0] = -1;
	while (++pixel[0] < vp.h)
	{
		pixel[1] = -1;
		while (++pixel[1] < vp.w)
		{
			
		}
	}
}

int	main(int ac, char **av)
{
	t_scene		scene;
	t_viewport	vp;
	t_mat4		view_mat;

	if (!valid_arg(ac, av))
		return (1);
	get_input(av[1], &scene);
	init_viewport(&vp, scene.cam);
	view_mat = get_view_matrix(scene.cam);
	convert_to_cam_view(view_mat, &scene);
	print_scene(&scene);
	render(vp, scene);
	return (0);
}
