/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 00:07:16 by suchua            #+#    #+#             */
/*   Updated: 2023/08/17 00:07:22 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	thread_runner(t_viewport *vp)
{
	int			i;
	int			start_y;
	t_render	r;

	r.lines_per_thread = (int) vp->h / THREAD_NUM;
	r.remaining_lines = (int) vp->h % THREAD_NUM;
	i = -1;
	start_y = 0;
	while (++i < THREAD_NUM)
	{
		r.data[i].vp = vp;
		r.data[i].start_y = start_y;
		r.data[i].end_y = start_y + r.lines_per_thread;
		if (r.remaining_lines > 0)
		{
			r.data[i].end_y++;
			r.remaining_lines--;
		}
		pthread_create(&r.th[i], NULL, routine, &r.data[i]);
		start_y = r.data[i].end_y;
	}
	i = -1;
	while (++i < THREAD_NUM)
		pthread_join(r.th[i], NULL);
}

void	render(t_viewport *vp)
{
	int			i;
	t_th		data;

	if (vp->edit)
	{
		clean_img(vp);
		data.start_y = 0;
		data.end_y = (int) vp->h;
		data.vp = vp;
		routine(&data);
	}
	else
	{
		printf("\n######## RENDERING ########\n");
		thread_runner(vp);
	}
	mlx_put_image_to_window(vp->mlx, vp->win, vp->img.ptr, 0, 0);
	if (!vp->edit)
	{
		printf("DONE\n\n");
		printf("Press key SHIFT to enter EDIT MODE\n");
	}
}
