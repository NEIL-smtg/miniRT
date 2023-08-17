/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:00:07 by suchua            #+#    #+#             */
/*   Updated: 2023/07/27 22:57:18 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <stdio.h>

void	print_vec3(t_vec3 v, char *name)
{
	printf("%s = %f %f %f\n", name, v.x, v.y, v.z);
}

t_vec3	vec3_mul(double scalar, t_vec3 v)
{
	return (new_vec3(
			scalar * v.x,
			scalar * v.y,
			scalar * v.z
		));
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return (new_vec3(
			a.x - b.x,
			a.y - b.y,
			a.z - b.z
		));
}

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return (new_vec3(
			a.x + b.x,
			a.y + b.y,
			a.z + b.z
		));
}
