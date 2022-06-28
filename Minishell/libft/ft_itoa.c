/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:21:54 by elouisia          #+#    #+#             */
/*   Updated: 2022/03/28 15:14:16 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getsize(long int nb)
{
	int	i;

	i = 1;
	if (nb < 0)
	{
		nb = -nb;
		i++;
	}
	while (nb > 9)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*dst;
	int				size;
	long int		nb;

	nb = n;
	size = ft_getsize(nb);
	dst = ft_calloc(sizeof(char), (size + 1));
	if (!dst)
		return (0);
	if (nb < 0)
	{
		nb = -nb;
		dst[0] = '-';
	}
	dst[size] = '\0';
	while (--size >= 0 && !dst[size])
	{
		dst[size] = (nb % 10) + 48;
		nb = (nb / 10);
	}
	return (dst);
}
