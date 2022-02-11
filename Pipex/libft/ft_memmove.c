/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:33:40 by elouisia          #+#    #+#             */
/*   Updated: 2021/12/08 15:16:14 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*str;
	unsigned char	*dst;
	int				l;

	str = (unsigned char *)src;
	dst = (unsigned char *)dest;
	l = (int)n - 1;
	if (!dest && !src)
		return (0);
	if (dest > src)
	{
		while (l >= 0)
		{
			dst[l] = str[l];
			l--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
/*
#include <stdio.h>

void	*ft_memcpy(void *dest, const void *src, size_t n);

int	main(void)
{
	char *src = "ijklmno";
	char *src2 = "ijklmno";
	char *src3 = "ijklmno";
	char *src4 = "ijklmno";
	char dst[50] = "abcdefg";
	char dst2[50] = "abcdefg";
	char dst3[50] = "abcdefg";
	char dst4[50] = "abcdefg";
	printf("Before : %s\n", src);
	printf("(ma fonction) : %s\n", (char *)ft_memmove(src, src + 3, 3));
	printf("(base) : %s\n", (char *)memmove(src2, src2 + 3, 3));
	printf("(ma memcpy) : %s\n", (char *)ft_memcpy(dst3, src3 + 3, 3));
	printf("(memcpy) : %s\n", (char *)memcpy(dst4, src4 +3, 3));
}*/
