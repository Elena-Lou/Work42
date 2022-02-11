/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:51:30 by elouisia          #+#    #+#             */
/*   Updated: 2021/11/26 14:58:23 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && i < n - 1 && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*
#include <stdio.h>

int	main(void)
{
	char	str1[] = "Hello";
	char	str2[] = "Hellp";
	char	str3[] = "Gello";

	printf("%d\n", ft_strncmp(str1, str2, 6));
	printf("%d\n", strncmp(str1, str2, 6));
	printf("%d\n", ft_strncmp(str1, str3, 6));
	printf("%d\n", strncmp(str1, str3, 6));	
}
*/
