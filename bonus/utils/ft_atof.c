/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 23:50:35 by suchua            #+#    #+#             */
/*   Updated: 2023/05/22 20:29:10 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	get_decimal(char *s)
{
	int		i;
	double	total;

	if (*s != '.')
		return (0);
	i = 1;
	total = 0.0f;
	while (s[i])
	{
		total += (s[i] - '0') / pow(10, i);
		++i;
	}
	return (total);
}

double	ft_atof(char *s)
{
	double	total;
	int		i;
	double	sign;

	total = 0.0;
	sign = 1.0f;
	i = 0;
	while (ft_isspace(s[i]))
		++i;
	if (s[i] == '-')
		sign *= -1.0f;
	if (s[i] == '+' || s[i] == '-')
		++i;
	while (s[i] >= '0' && s[i] <= '9')
		total = total * 10 + s[i++] - '0';
	total += get_decimal(&s[i]);
	return (total * sign);
}
