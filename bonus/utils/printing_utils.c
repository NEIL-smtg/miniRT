/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:55:58 by mmuhamad          #+#    #+#             */
/*   Updated: 2023/08/09 13:58:17 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_obj(t_obj *tmp)
{
	if (tmp->type == SPHERE)
		printf("SPHERE\t{\n");
	else if (tmp->type == PLANE)
		printf("PLANE\t{\n");
	else if (tmp->type == CONE)
		printf("CONE\t{\n");
	else if (tmp->type == LIGHT)
		printf("LIGHT\t{\n");
	else
		printf("CYLINDER\t{\n");
}
