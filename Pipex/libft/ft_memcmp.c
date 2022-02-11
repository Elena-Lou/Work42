/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:31:35 by elouisia          #+#    #+#             */
/*   Updated: 2021/12/07 16:23:54 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	*str2;

	i = 0;
	str = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n <= 0)
		return (0);
	while (i < n && str[i] == str2[i])
		i++;
	if (i == n)
		return ((str[i - 1] - str2[i - 1]));
	return (str[i] - str2[i]);
}

/*
#include <stdio.h>
int	main(void)
{
	char s[] = {0, 0, 127, 0};
	char s2[] = {0, 0, 42, 0};

	printf("ma fonction : %d\n", ft_memcmp(s, s2, 5));
	printf("base: %d\n", memcmp(s, s2, 5));
	return (0);
}*/
