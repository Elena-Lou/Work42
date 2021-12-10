/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:06:28 by elouisia          #+#    #+#             */
/*   Updated: 2021/12/09 18:28:58 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int					i;
	int					neg;
	long long int		nb;

	i = 0;
	neg = 1;
	nb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		neg *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] - '0');
		i++;
	}
//	if (nb > 214483647 || nb < -2147483648)
//		return (0);
	return (nb * neg);
}
/*
#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	printf("ma fonction %d\n", ft_atoi("+-12"));
	printf("fonction de base %d\n", atoi("+-12"));
	return (0);
}*/
