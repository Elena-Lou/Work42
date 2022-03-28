/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:04:46 by elouisia          #+#    #+#             */
/*   Updated: 2021/11/29 16:22:51 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	*dst;

	i = 0;
	str = (unsigned char *)src;
	dst = (unsigned char *)dest;
	while (i < n)
	{
		dst[i] = str[i];
		i++;
	}
	return (dst);
}
/*
#include <stdio.h>

int	main(void)
{
	char src[50] = "TTTTTTTTTTTTTTTT";
	char src2[50] = "TTTTTTTTTTTTTTTT";
	char dest[50] = "A long time";
	char dest2[50] = "A long time";
	printf("(ma fonction) : %s\n", (char *)ft_memcpy(dest, src, 6));
	printf("(fonction de base) : %s\n", (char *)memcpy(dest2, src2, 6));
}*/
