/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 00:56:07 by suchua            #+#    #+#             */
/*   Updated: 2023/04/27 01:28:40 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	objs_lst_addback(t_objs **objs, t_objs **new)
{
	t_objs	*tmp;

	tmp = *objs;
	if (!objs || !*objs)
		*objs = *new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = *new;
	}
}
