/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdubilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:41:53 by elouisia          #+#    #+#             */
/*   Updated: 2022/06/27 15:47:28 by jdubilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char	*cpy_only_char(char s2)
{
	char	*dest;

	dest = malloc(sizeof(char) * 2);
	if (!dest)
		return (NULL);
	dest[0] = s2;
	dest[1] = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char s2)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
	{
		dest = cpy_only_char(s2);
		return (dest);
	}
	dest = malloc(sizeof(char) * (ft_strlen(s1) + 2));
	if (!dest)
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[j + i] = s2;
	i++;
	dest[j + i] = '\0';
	if (s1)
		free(s1);
	return (dest);
}
