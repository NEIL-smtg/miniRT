/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 00:44:26 by suchua            #+#    #+#             */
/*   Updated: 2023/05/04 02:07:29 by suchua           ###   ########.fr       */
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

# define SPHERE		1
# define PLANE		2
# define CYLINDER	3

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	t_scene	sc;
}	t_mlx;

////////////////////////////////////////////////////////
/////////////////FUNCTION PROTOTYPE/////////////////////
////////////////////////////////////////////////////////

//atof
double		ft_atof(char *s);

//valid arg
int			valid_arg(int ac, char **av);

#endif