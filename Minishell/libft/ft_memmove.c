/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:33:40 by elouisia          #+#    #+#             */
/*   Updated: 2022/03/28 15:14:46 by elouisia         ###   ########.fr       */
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
