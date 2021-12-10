/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:38:02 by elouisia          #+#    #+#             */
/*   Updated: 2021/11/29 16:18:12 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (str);
}
/*
#include <stdio.h>

int	main(void)
{
	char	str[50] = "In a galaxy far far away";
	char	str2[50] = "In a galaxy far far away";
	printf("Before : %s\n", str);
	printf("Before : %s\n", str2);
	printf("%s\n", (char *)ft_memset(str, 'T', 4*sizeof(char)));
	printf("base) : %s\n", (char *)memset(str2, 'T', 4*sizeof(char)));	
}*/
