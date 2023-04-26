/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 00:44:26 by suchua            #+#    #+#             */
/*   Updated: 2023/04/26 17:19:17 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../Libft/include/libft.h"
# include <mlx.h>
# include <math.h>
# include <errno.h>
# include <fcntl.h>
# include "scene.h"

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	int		x;
	int		y;
}	t_mlx;


#endif
