/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 00:44:15 by suchua            #+#    #+#             */
/*   Updated: 2023/06/29 20:10:55 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mat3	get_transform_matrix(t_camera cam)
{
	t_vec3	right;
	t_vec3	up;
	t_vec3	forward;

	forward = normalize(cam.dir);
	up = new_vec3(0, 1, 0);
	if (forward.z == 1.0)
		right = new_vec3(1, 0, 0);
	else if (forward.z == -1.0)
		right = new_vec3(-1, 0, 0);
	else
	{
		up = normalize(new_vec3(forward.y, -forward.x, 0));
		right = vec3_cross(right, forward);
	}
	return (new_mat3(
		up,
		right,
		forward
	));
}

void	init_viewport(t_viewport *vp, t_camera cam)
{
	vp->aspect_ratio = 16.0 / 9.0;
	vp->h = HEIGHT;
	vp->w = HEIGHT * vp->aspect_ratio;
	vp->origin = cam.pos;
	vp->focal = get_focal_length(cam.fov, vp->w);
	vp->transform_mat = get_transform_matrix(cam);
}

t_vec3	convert_to_cam(t_mat3 transform_mat, t_vec3 v)
{
	t_vec3	res;

	res.x = vec3_dot(transform_mat.r1, v);
	res.y = vec3_dot(transform_mat.r2, v);
	res.z = vec3_dot(transform_mat.r3, v);
	return (res);
}

void	world_to_camera(t_mat3 transform_mat, t_scene *sc)
{
	t_obj	*tmp;

	sc->cam.pos = convert_to_cam(transform_mat, sc->cam.pos);
	sc->cam.dir = convert_to_cam(transform_mat, sc->cam.dir);
	sc->light.pos = convert_to_cam(transform_mat, sc->light.pos);
	tmp = sc->obj;
	while (tmp)
	{
		tmp->center = convert_to_cam(transform_mat, tmp->center);
		if (tmp->type != SPHERE)
			tmp->dir = convert_to_cam(transform_mat, tmp->dir);
		tmp = tmp->next;
	}
}

t_vec3	get_ray_dir(int pixel[2], t_viewport *vp, t_vec3 cam_origin)
{
	t_vec3	pixel_coord;

	pixel_coord.x = (double) pixel[0] - vp->w / 2.0;
	pixel_coord.y = (double) pixel[1] - vp->h / 2.0;
	pixel_coord.z = vp->focal;
	return (normalize(pixel_coord));
}

double	solve_quadratic(double a, double b, double c)
{
	double	discriminant;
	double	t1;
	double	t2;

	discriminant = pow(b, 2) - 4.0 * a * c;
	if (discriminant <= 0.0f || (2.0 * a) <= 1e-6)
		return (-1.0);
	t1 = (-b - sqrt(discriminant) / (2.0 * a));
	t2 = (-b + sqrt(discriminant) / (2.0 * a));
	if (t1 > 0.0f && t2 > 0.0f && t1 < t2)
		return (t1);
	if (t1 > 0.0f && t2 > 0.0f && t2 < t1)
		return (t2);
	if (t1 > 0.0f)
		return (t1);
	if (t2 > 0.0f)
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
		-2.0f * vec3_dot(obj_vec, ray.dir),
		vec3_dot(obj_vec, obj_vec) - pow(obj->d / 2.0f, 2)
	);
	return (dist);
}

void	fill_color(t_rgb color, t_viewport *vp, int pixel[2])
{
	unsigned char	*data;
	int				index;

	data = (unsigned char *) vp->img.data_addr;
	index = (pixel[1] * vp->img.line_size + pixel[0] * (vp->img.bpp / 8));
	data[index] = (unsigned char) color.b;
	data[index + 1] = (unsigned char) color.g;
	data[index + 2] = (unsigned char) color.r;
}

void	render(t_viewport *vp, t_scene sc)
{
	int		pixel[2];
	t_ray	ray;

	ray.origin = sc.cam.pos;
	pixel[1] = -1;
	while (++pixel[1] < (int) vp->h)
	{
		pixel[0] = -1;
		while (++pixel[0] < (int) vp->w)
		{
			ray.dir = get_ray_dir(pixel, vp, ray.origin);
			if (sphere_intersection(ray, sc.obj) != -1.0)
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
	
	if (!valid_arg(ac, av))
		return (1);
	get_input(av[1], &scene);
	init_viewport(&vp, scene.cam);
	// print_scene(&scene);
	world_to_camera(vp.transform_mat, &scene);
	print_scene(&scene);
	create_mlx(&vp);
	render(&vp, scene);
	mlx_loop(vp.mlx);
	return (0);
}
