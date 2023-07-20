/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 01:43:56 by suchua            #+#    #+#             */
/*   Updated: 2023/07/21 02:28:50 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_mat4	get_x_rotation_mat(double theta)
{
	t_mat4	rot;

	rot.r1 = new_vec4(1, 0, 0 ,0);
	rot.r2 = new_vec4(0, cos(theta), -sin(theta), 0);
	rot.r3 = new_vec4(0, sin(theta), cos(theta), 0);
	rot.r4 = new_vec4(0, 0, 0, 1);
	return (rot);
}
