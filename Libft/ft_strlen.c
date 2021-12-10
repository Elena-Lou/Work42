/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:26:39 by elouisia          #+#    #+#             */
/*   Updated: 2021/11/26 14:58:03 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
/*
#include <stdio.h>
int	main(int ac, char **ar)
{
	if (ac == 2)
		printf("ma fonction : %ld\n", ft_strlen(ar[1]));
		printf("base : %ld\n", strlen(ar[1]));
	return 0;
}*/