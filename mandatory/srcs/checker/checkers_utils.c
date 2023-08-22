/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:59:18 by mmuhamad          #+#    #+#             */
/*   Updated: 2023/08/22 17:43:48 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	valid_num2d(char **sp)
{
	int		i;
	int		j;
	int		dot;

	dot = 0;
	i = -1;
	while (sp[++i])
	{
		j = -1;
		dot = 0;
		while (sp[i][++j])
		{
			if (sp[i][j] == '.')
			{
				if (++dot > 1)
					return (false);
				continue ;
			}
			if (sp[i][j] == '-' || sp[i][j] == '+')
				continue ;
			if (!ft_isdigit(sp[i][j]))
				return (false);
		}
	}
	return (true);
}

bool	valid_num(char *sp)
{
	int		i;
	int		dot;

	dot = 0;
	i = -1;
	while (sp[++i])
	{
		if (sp[i] == '.')
		{
			dot ++;
			if (dot > 1)
				return (false);
			continue ;
		}
		if (sp[i] == '-' || sp[i] == '+')
			continue ;
		if (!ft_isdigit(sp[i]))
			return (false);
	}
	return (true);
}

int	valid_range_str(double from, double to, char *sp, char *sp2)
{
	int	nb;

	if (!valid_num(sp))
		return (0);
	if (sp2 && !valid_num(sp2))
		return (0);
	if (sp2)
	{
		nb = atan(ft_atof(sp) / ft_atof(sp2));
		return (nb >= from && nb <= to);
	}
	nb = ft_atof(sp);
	return (nb >= from && nb <= to);
}
