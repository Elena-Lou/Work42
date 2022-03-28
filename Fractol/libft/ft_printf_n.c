/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_n.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 11:44:35 by elouisia          #+#    #+#             */
/*   Updated: 2022/01/18 15:40:33 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_getsize(long int nb)
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

int	ft_print_nbr(int n)
{
	long int	nb;

	nb = n;
	if (nb == -2147483648)
		write (1, "-2147483648", 11);
	else
	{
		if (nb < 0)
		{
			ft_print_char('-');
			nb = -n;
		}
		if (nb >= 0 && nb < 10)
			ft_print_char(nb + 48);
		else
		{
			ft_print_nbr(nb / 10);
			ft_print_nbr(nb % 10);
		}
	}
	return (ft_getsize(n));
}

int	ft_print_unbr(unsigned int n)
{
	unsigned long int	nb;

	nb = n;
	if (nb < 10)
		ft_print_char(nb + 48);
	else
	{
		ft_print_unbr(nb / 10);
		ft_print_unbr(nb % 10);
	}
	return (ft_getsize(n));
}
