/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:31:35 by elouisia          #+#    #+#             */
/*   Updated: 2022/03/28 15:14:32 by elouisia         ###   ########.fr       */
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
