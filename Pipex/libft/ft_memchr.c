/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:10:44 by elouisia          #+#    #+#             */
/*   Updated: 2021/11/29 17:52:18 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	u;

	i = 0;
	str = (unsigned char *)s;
	u = (unsigned char)c;
	while (i < n)
	{
		if (str[i] == u)
			return (&str[i]);
		i++;
	}
	return (0);
}
