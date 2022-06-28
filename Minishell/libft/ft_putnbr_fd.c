/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:16:00 by elouisia          #+#    #+#             */
/*   Updated: 2021/12/07 16:19:34 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int		nb;

	nb = n;
	if (nb == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (nb < 0)
		{
			ft_putchar_fd('-', fd);
			nb = -n;
		}
		if (nb >= 0 && nb < 10)
			ft_putchar_fd((nb + 48), fd);
		else
		{	
			ft_putnbr_fd((nb / 10), fd);
			ft_putnbr_fd((nb % 10), fd);
		}
	}
}
