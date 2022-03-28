/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:15:22 by elouisia          #+#    #+#             */
/*   Updated: 2021/12/07 16:23:31 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*dst;

	i = 0;
	if (!s)
		return (0);
	if (start > ft_strlen(s))
		dst = malloc(sizeof(char));
	else if (len > ft_strlen(s) - start)
		dst = malloc(sizeof(char) * (ft_strlen(s) - start) + 1);
	else
		dst = malloc(sizeof(char) * len + 1);
	if (!dst)
		return (0);
	while (start <= ft_strlen(s) && i < len && s[start + i])
	{
		dst[i] = s[start + i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
