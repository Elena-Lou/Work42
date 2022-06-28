/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdubilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:29:31 by elouisia          #+#    #+#             */
/*   Updated: 2022/05/26 21:32:53 by jdubilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	s_length;
	char	*str;
	size_t	i;

	str = (char *)src;
	s_length = ft_strlen(str);
	i = 0;
	if (size)
	{
		while ((i < size) && (str[i]))
		{
			dst[i] = str[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (s_length);
}
