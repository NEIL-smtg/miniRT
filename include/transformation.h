/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:41:37 by suchua            #+#    #+#             */
/*   Updated: 2023/07/26 00:10:56 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORMATION_H
# define TRANSFORMATION_H

# include "scene.h"
# include "vector.h"

# define ANGLE_ROTATION	10

enum	e_movement
{
	left,
	right,
	up,
	down,
	forward,
	backward
};

enum	e_rotation
{
	to_origin,
	revert	
};

// cam rotation
void	ft_cam_panning(int keycode, t_viewport *vp);

// translation
bool	is_translation_key(int keycode);
void	translation(int keycode, t_viewport *vp);

#endif
