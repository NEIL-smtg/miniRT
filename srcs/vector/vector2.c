/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:00:07 by suchua            #+#    #+#             */
/*   Updated: 2023/05/28 19:20:44 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_vector(t_vec v, char *name)
{
	printf("%s = %f %f %f\n", name, v.x, v.y, v.z);
}

double	get_radian(int angle)
{
	return ((double) angle * M_PI / 180);
}
