/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 00:44:15 by suchua            #+#    #+#             */
/*   Updated: 2023/06/27 19:32:49 by suchua           ###   ########.fr       */
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

void	convert_settings_to_cam_view(t_mat4 view_mat, t_scene *sc)
{
	t_vec4	tmp_c;
	t_vec4	tmp_n;

	tmp_c = convert_to_4d(sc->cam.pos);
	tmp_n = convert_to_4d(sc->cam.dir);
	sc->cam.pos = convert_to_3d(mat4_mul(view_mat, tmp_c));
	sc->cam.dir = convert_to_3d(mat4_mul(view_mat, tmp_n));
	tmp_c = convert_to_4d(sc->light.pos);
	sc->light.pos = convert_to_3d(mat4_mul(view_mat, tmp_c));
}

void	convert_to_cam_view(t_mat4 view_mat, t_scene *sc)
{
	t_obj	*tmp;
	t_vec4	tmp_c;
	t_vec4	tmp_n;

	convert_settings_to_cam_view(view_mat, sc);
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

t_vec3	get_ray_dir(int pixel[2], t_viewport vp)
{
	return (normalize(new_vec3(
		(double) pixel[0] - vp.w / 2,
		(double) pixel[1] - vp.h / 2,
		vp.focal
	)));
}

double	solve_quadratic(double a, double b, double c)
{
	double	discriminant;
	double	sqrt_d;
	double	t1;
	double	t2;

	discriminant = pow(b, 2) * 4 * a * c;
	if (discriminant < 0)
		return (-1.0);
	sqrt_d = sqrt(discriminant);
	t1 = (-b - sqrt_d) / (2 * a);
	t2 = (-b + sqrt_d) / (2 * a);
	if (t1 > 0 && t2 > 0)
		return (fmin(t1, t2));
	else if (t1 > 0)
		return (t1);
	else if (t2 > 0)
		return (t2);
	return (-1.0);
}

double	sphere_intersection(t_ray ray, t_obj *obj)
{
	double	dist;
	t_vec3	obj_vec;

	obj_vec = vec3_sub(obj->center, ray.origin);
	dist = solve_quadratic(
		vec3_dot(ray.dir, ray.dir),
		2.0f * vec3_dot(obj_vec, ray.dir),
		vec3_dot(obj_vec, obj_vec) - pow(obj->d / 2.0f, 2)
	);
	return (dist);
}

t_obj	*fill_pixel(t_ray ray, t_obj *obj)
{
	double	d[2];
	t_obj	*closest;

	d[1] = INFINITY;
	closest = NULL;
	while (obj)
	{
		if (obj->type == SPHERE)
		{
			d[0] = sphere_intersection(ray, obj);
			if (d[0] != -1.0 && d[0] < d[1])
			{
				d[1] = d[0];
				closest = obj;
			}
		}
		obj = obj->next;
	}
	return (closest);
}

void	fill_color(t_rgb color, t_viewport *vp, int pixel[2])
{
	unsigned char	*data;
	int				index;

	data = (unsigned char *) vp->img.data_addr;
	index = (pixel[1] * vp->img.line_size + pixel[0] * (vp->img.bpp / 8));
	data[index] = (unsigned int) rgb_to_int(color);
	data[index + 1] = (unsigned int) rgb_to_int(color);
	data[index + 2] = (unsigned int) rgb_to_int(color);
}

void	render(t_viewport *vp, t_scene sc)
{
	int		pixel[2];
	t_ray	ray;
	t_obj	*closest;

	pixel[1] = -1;
	ray.origin = sc.cam.pos;
	while (++pixel[1] < vp->h)
	{
		pixel[0] = -1;
		while (++pixel[0] < vp->w)
		{
			ray.dir = get_ray_dir(pixel, *vp);
			if (sphere_intersection(ray, sc.obj) != -1)
				fill_color(sc.obj->rgb, vp, pixel);
		}
	}
	mlx_put_image_to_window(vp->mlx, vp->win, vp->img.ptr, 0, 0);
}

void	create_mlx(t_viewport *vp)
{
	vp->mlx = mlx_init();
	vp->win = mlx_new_window(vp->mlx, (int) vp->w, (int) vp->h, TITLE);
	vp->img.ptr = mlx_new_image(vp->mlx, (int) vp->w, (int) vp->h);
	vp->img.data_addr = mlx_get_data_addr(
		vp->img.ptr,
		&vp->img.bpp,
		&vp->img.line_size,
		&vp->img.endian
	);
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
	create_mlx(&vp);
	render(&vp, scene);
	mlx_loop(vp.mlx);
	return (0);
}
