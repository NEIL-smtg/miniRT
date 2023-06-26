/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 02:47:28 by suchua            #+#    #+#             */
/*   Updated: 2023/06/27 02:48:37 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	convert_to_3d(t_vec4 v)
{
	return (new_vec3(
			v.x / v.w,
			v.y / v.w,
			v.z / v.w
	));
}

t_vec4	convert_to_4d(t_vec3 v)
{
	return (new_vec4(
		v.x,
		v.y,
		v.z,
		1
	));
}
