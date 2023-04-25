/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:32:36 by suchua            #+#    #+#             */
/*   Updated: 2023/04/07 20:10:23 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	*ft_memcpy(void *dest, const void *src, size_t	n)
{
	size_t	i;
	char	*s;
	char	*d;

	i = 0;
	if (!dest && !src)
		return (NULL);
	s = (char *)src;
	d = (char *)dest;
	while (i < n)
	{
		*d++ = *s++;
		i++;
	}
	return (dest);
}

#include <string.h>

// int main(void)
// {
//     char ori[100] = "i am going to sleep tomorrow hehehehehhe 12314";
//     char *src = ori + 3;
//     // src = am going to sleep;
//     char *dst = ori + 5;
//     // dst = oing to sleep;
//     // ft_memcpy(dst, src, 15);
// 	ft_memcpy((void *)dst, (const void*) src, 15);
//     printf("%s\n", ori);

//     char ori1[100] = "i am going to sleep tomorrow hehehehehhe 12314";
//     char *src1 = ori1 + 3;
//     // src = am going to sleep;
//     char *dst1 = ori1 + 5;
//     // dst = oing to sleep;
//     // memcpy(dst1, src1, 15);
// 	memcpy((void *)dst, (const void*) src1, 15);
//     printf("%s", ori);
// }
