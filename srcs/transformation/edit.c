/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:30:19 by mmuhamad          #+#    #+#             */
/*   Updated: 2023/07/25 18:50:35 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_user_command(void)
{
	char	*comm;

	printf("TYPE AN ELEMENT TO EDIT : ");
	comm = get_next_line(0);
	if (!ft_strncmp(comm, "sp", 2))
		return (1);
	return (0);
}

void	render_edit(t_viewport *vp, t_scene sc)
{
	int		pixel[2];
	t_ray	ray;
	t_obj	*closest;
	double	t;

	printf("EDIT MODE....\n");
	clean_img(vp);
	ray.origin = sc.cam.pos;
	pixel[1] = -1;
	while (++pixel[1] < (int) vp->h)
	{
		pixel[0] = -1;
		while (++pixel[0] < (int) vp->w)
		{
			closest = NULL;
			ray.dir = get_ray_dir(pixel, vp, ray.origin);
			t = get_closest_obj(ray, sc.obj, &closest);
			if (closest)
			{
				fill_color(closest->rgb, vp, pixel);
			}
		}
	}
	mlx_put_image_to_window(vp->mlx, vp->win, vp->img.ptr, 0, 0);
	// printf("EXIT EDITING MODE\n");
}

// void	ft_get_input_sp(t_obj	*closest)
// {
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	printf("%u\n", closest->type);
	// while (i < 7)
	// {
		// if (i == 1)
		// {
		// 	// printf("sp x coordinate : ");
		// 	write(1, "sp x coordinate : ", 18);
		// }
		// else if (i == 2)
		// 	printf("sp y coordinate : ");
		// else if (i == 3)
		// 	printf("sp z coordinate : ");
		// else if (i == 4)
		// 	printf("sp diameter : ");
		// else if (i == 5)
		// 	printf("sp red color num : ");
		// else if (i == 6)
		// 	printf("sp green color num : ");
		// else if (i == 7)
		// 	printf("sp blue color num : ");
		// tmp = get_next_line(0);
		// if (!tmp)
		// 	break ;
		// if (*tmp == '\0')
		// 	break ;
		// if (ft_chck_input(tmp))
		// {
		// 	write(2, "Error\n", 6);
		// 	exit (0);
		// }
		// if (i == 1)
		// 	closest->center.x = ft_atof(tmp);
		// else if (i == 2)
		// 	closest->center.y = ft_atof(tmp);
		// else if (i == 3)
		// 	closest->center.z = ft_atof(tmp);
		// else if (i == 4)
		// 	closest->d = ft_atof(tmp);
		// else if (i == 5)
		// 	closest->rgb.r = ft_atof(tmp);
		// else if (i == 6)
		// 	closest->rgb.g = ft_atof(tmp);
		// else if (i == 7)
		// 	closest->rgb.b = ft_atof(tmp);
	// 	i++;
	// }
// 	printf("sp diameter : ");
// 	// tmp = get_next_line(0);
// 	closest->d = ft_atof(tmp);
// }

// void	edit_element(t_obj	*closest)
// {
// 	printf("%u\n", closest->type);
// 	if (closest->type == 0)
// 		ft_get_input_sp(closest);
	// else if (closest->type == 1)
	// {
	// 	ft_get_input_cy(closest);
	// }
	// else if (closest->type == 2)
	// {
	// 	ft_get_input_pl(closest);
	// }
// }

// void	ft_obj_panning(t_viewport *vp, t_obj *closest)
// {
// 	t_quat	q;
// 	t_vec3	rot_center;
// 	t_vec3	rot_axis;
// 	int		angle;

// 	angle = ANGLE_ROTATION;
// 	// rot_axis = get_rotation_axis(keycode, vp->view_mat, &angle);
// 	rot_axis = get_cam_up(vp->view_mat);
// 	rot_center = closest->center;
// 	origin_translation(vp->scene, rot_center, to_origin);
// 	q = get_quaternion(get_radian(angle), rot_axis);
// 	quaternion_rotation(q, vp);
// 	origin_translation(vp->scene, rot_center, revert);
// 	// print_scene(vp->scene);
// 	render(vp, *vp->scene);
// }

int	mouse_event(int button, int x, int y, t_viewport *vp)
{
	int		pixel[2];
	t_ray	ray;
	double	t;
	t_rgb	cp;
	t_obj	*closest;

	pixel[0] = x;
	pixel[1] = y;
	ray.origin = vp->scene->cam.pos;
	closest = NULL;
	ray.dir = get_ray_dir(pixel, vp, ray.origin);
	t = get_closest_obj(ray, vp->scene->obj, &closest);
	if (closest)
	{
		cp = new_rgb(closest->rgb.r, closest->rgb.g, closest->rgb.b);
		closest->rgb = new_rgb(255, 0, 0);
	}
	render_edit(vp, *vp->scene);
	if (closest)
		closest->rgb = new_rgb(cp.r, cp.g, cp.b);
	// ft_obj_panning(vp, closest);
	// continue-code-here
	return (0);
}

void	ft_edit(t_viewport *vp)
{
	int		type;

	vp->edit = true;
	render_edit(vp, *vp->scene);
	mlx_mouse_hook(vp->win, mouse_event, vp);
}
