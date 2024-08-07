/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_fix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neilsundae <suchua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:54:33 by suchua            #+#    #+#             */
/*   Updated: 2023/09/08 02:36:13 by neilsundae       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	obj_is_fix(t_obj *obj, enum e_type shape, char *name, int line)
{
	t_obj	*tmp;
	int		count;
	int		fix;

	tmp = obj;
	count = 0;
	fix = 0;
	while (tmp)
	{
		if (tmp->type == shape)
			++count;
		if (tmp->type == shape && tmp->fix)
			++fix;
		tmp = tmp->next;
	}
	if (!(fix > 1 || (fix && count)))
		return (1);
	printf("Error !!\n");
	line_error(line);
	printf("Capitalize specifier can only be specified once !!\n");
	printf("Error : (%s)\n", name);
	return (0);
}

static void	fix_error(int *acl, int line)
{
	printf("Error !!\n");
	line_error(line);
	printf("Capitalize specifier can only be specified once !!\n");
	if (acl[0] > 1)
		printf("Error : (%s)\n", "AMBIENT");
	if (acl[1] > 1)
		printf("Error : (%s)\n", "CAMERA");
	if (acl[2] > 1)
		printf("Error : (%s)\n", "LIGHT");
	if ((acl[2] && acl[3]))
		printf("Error : (%s)\n", "LIGHT & light");
}

int	is_fix(t_scene *sc, int *acl, int line)
{
	t_obj	*obj;

	obj = sc->obj;
	if (acl[0] > 1 || acl[1] > 1 || acl[2] > 1 || (acl[2] && acl[3]))
	{
		fix_error(acl, line);
		free(acl);
		return (0);
	}
	if (!acl[0] || !acl[1] || !acl[2] || !(acl[2] + acl[3]))
	{
		printf("Error !!\n");
		line_error(line);
		printf("The scene must contain at least 1 camera(C), ");
		printf("light(L) and ambient(A) !!\n");
		free(acl);
		return (0);
	}
	free(acl);
	return (obj_is_fix(obj, SPHERE, "SPHERE", line)
		&& obj_is_fix(obj, PLANE, "PLANE", line)
		&& obj_is_fix(obj, CYLINDER, "CYLINDER", line));
}
