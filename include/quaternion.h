/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 23:43:41 by suchua            #+#    #+#             */
/*   Updated: 2023/07/24 00:32:57 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATERNION_H
# define QUATERNION_H

# include "matrix.h"

typedef struct s_quaternion
{
	t_vec4	quaternion;
	t_vec4	conjugate;
}	t_quat;

t_quat	get_quaternion(double rad, t_vec3 dir);
t_vec3	rotate(t_vec3 pt, t_quat q);

#endif
