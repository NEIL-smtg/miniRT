/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 03:55:54 by suchua            #+#    #+#             */
/*   Updated: 2023/05/28 17:53:55 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static char	**recursive_split(char const *s, int depth)
{
	int		i;
	char	*str;
	char	**strs;

	i = 0;
	while (s[i] && !ft_isspace(s[i]))
		++i;
	str = ft_substr(s, 0, (size_t) i);
	if (!str)
		return (NULL);
	while (s[i] && ft_isspace(s[i]))
		++i;
	if (s[i])
		strs = recursive_split(s + i, depth + 1);
	else
		strs = ft_calloc(depth + 2, sizeof(char *));
	if (!strs)
		return (NULL);
	strs[depth] = str;
	return (strs);
}

char	**rt_split(char const *s)
{
	if (!s)
		return (NULL);
	while (*s && ft_isspace(*s))
		s++;
	if (!*s)
		return (ft_calloc(1, sizeof(char *)));
	return (recursive_split(s, 0));
}
