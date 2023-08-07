/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:56:28 by suchua            #+#    #+#             */
/*   Updated: 2023/08/07 21:32:58 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	get_bump_effect_normal(t_obj *obj, const t_vec3 inter, t_vec3 n, \
		t_img texture)
{
	double	u;
	double	v;

	if (!obj->bump || !texture.ptr)
		return (n);
	obj->get_uv(&inter, &u, &v, obj);
}
