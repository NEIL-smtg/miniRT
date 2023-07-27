/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_property.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:56:02 by suchua            #+#    #+#             */
/*   Updated: 2023/07/27 17:39:08 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void    apply_edit(int key, t_obj *selected)
{
    if (selected->edit_d && key == KEY_PLUS)
    {
        selected->d += 0.5;
        printf("Diameter increased.\n");
    }
    else if (selected->edit_d && key == KEY_MINUS)
    {
        selected->d -= 0.5;
        printf("Diameter decreased.\n");
    }
    else if (selected->type == CYLINDER && selected->edit_h && key == KEY_PLUS)
    {
        selected->h += 0.5;
        printf("Height increased.\n");
    }
    else if (selected->type == CYLINDER && selected->edit_h && key == KEY_MINUS)
    {
        selected->h -= 0.5;
        printf("Height decreased.\n");
    }
}

static void    edit_msg(bool edit, const char *type)
{
    if (edit)
        printf("\nYou can edit the %s now\n", type);
    else if (!ft_strncmp("Height", type, ft_strlen(type)))
        printf("\n%s locked.\nPress %c to edit %s again.\n", type, 'H', type);
    else if (!ft_strncmp("Diameter", type, ft_strlen(type)))
        printf("\n%s locked.\nPress %c to edit %s again.\n", type, 'J', type);
}

static void    height_handler(t_obj *selected)
{
    if (selected->edit_d)
    {
        selected->edit_d = false;
        edit_msg(selected->edit_d, "Diameter");
    }
    selected->edit_h = !selected->edit_h;
    edit_msg(selected->edit_h, "Height");
}

static void    diameter_handler(t_obj *selected)
{
    if (selected->edit_h)
    {
        selected->edit_h = false;
        edit_msg(selected->edit_d, "Height");
    }
    selected->edit_d = !selected->edit_d;
    edit_msg(selected->edit_d, "Diameter");
}

void	edit_property(int key, t_obj *selected)
{
	if ((key != KEY_J && key != KEY_H && key != KEY_MINUS && key != KEY_PLUS)
		|| selected->type == PLANE)
		return ;
	if (selected->fix)
	{
		printf("This object cannot be edit !!\n");
		return ;
	}
	if (key == KEY_J && selected->type != PLANE)
		diameter_handler(selected);
	else if (key == KEY_H && selected->type == CYLINDER)
		height_handler(selected);
	else if (selected->edit_d || selected->edit_h)
		apply_edit(key, selected);
}