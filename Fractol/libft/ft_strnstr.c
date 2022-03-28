/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:10:19 by elouisia          #+#    #+#             */
/*   Updated: 2021/11/29 18:28:44 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*haystack;
	char	*needle;

	i = 0;
	j = 0;
	haystack = (char *)big;
	needle = (char *)little;
	if (!(*needle))
		return (haystack);
	while (i < len && haystack[i])
	{
		j = 0;
		while (i + j < len && (haystack[i + j] == needle[j]) && needle[j])
		{
			j++;
			if (needle[j] == '\0')
				return (&haystack[i]);
		}
		i++;
	}
	return (0);
}
