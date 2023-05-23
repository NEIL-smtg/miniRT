/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 02:03:41 by suchua            #+#    #+#             */
/*   Updated: 2023/05/24 02:03:47 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
void	print_scene(t_scene *sc)
{
	return ;
	printf("A\t{\nfix : %d\nratio : %f\nrgb = %d,%d,%d\n}\n\n", sc->amblight.fix, sc->amblight.ratio, sc->amblight.rgb.r,sc->amblight.rgb.g,sc->amblight.rgb.b);
	printf("Cam\t{\nfix : %d\npos : %f,%f,%f\nvec : %f,%f,%f\nfov = %f\n}\n\n", sc->cam.fix, sc->cam.pos.x,sc->cam.pos.y,sc->cam.pos.z, sc->cam.vec.x,sc->cam.vec.y,sc->cam.vec.z, sc->cam.fov);
	printf("Light\t{\nfix : %d\npos : %f,%f,%f\nbrightness : %f\nrgb = %d,%d,%d\n}\n\n", sc->light.fix, sc->light.pos.x,sc->light.pos.y,sc->light.pos.z, sc->light.brightness, sc->light.rgb.r,sc->light.rgb.g,sc->light.rgb.b);
	
	t_pl	*plt = sc->pl;
	int i = 0;
	while (plt)
	{
		printf("PL_%d\t{\nfix : %d\npos : %f,%f,%f\nvec : %f,%f,%f\nrgb = %d,%d,%d\n}\n\n", i, plt->fix, plt->pos.x, plt->pos.y, plt->pos.z, plt->vec.x, plt->vec.y, plt->vec.z, plt->rgb.r, plt->rgb.g, plt->rgb.b);
		plt = plt->next;
		++i;
	}

	t_sp	*spt = sc->sp;
	i = 0;
	while (spt)
	{
		printf("SP_%d\t{\nfix : %d\npos : %f,%f,%f\ndiameter : %f\nrgb = %d,%d,%d\n}\n\n", i, spt->fix, spt->center.x, spt->center.y, spt->center.z, spt->d,  spt->rgb.r, spt->rgb.g, spt->rgb.b);
		spt = spt->next;
		++i;
	}

	t_cy	*clt = sc->cy;
	i = 0;
	while (clt)
	{
		printf("CY_%d\t{\nfix : %d\npos : %f,%f,%f\nvec : %f,%f,%f\nrgb = %d,%d,%d\ndiameter : %f, height : %f\n}\n\n", i, clt->fix, clt->center.x, clt->center.y, clt->center.z, clt->vec.x, clt->vec.y, clt->vec.z, clt->rgb.r, clt->rgb.g, clt->rgb.b, clt->d, clt->h);
		clt = clt->next;
		++i;
	}
}
