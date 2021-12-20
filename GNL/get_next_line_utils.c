/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 08:34:07 by elouisia          #+#    #+#             */
/*   Updated: 2021/12/20 14:54:33 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*s1;

	i = 0;
	s1 = (char *)s;
	if (!s)
		return (0);
	if ((unsigned char)c == '\0')
		return (&s1[ft_strlen(s1)]);
	while (s1[i])
	{
		if (s1[i] == (unsigned char) c)
			return (&s1[i]);
		i++;
	}
	return (0);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	*dst;

	i = 0;
	str = (unsigned char *)src;
	dst = (unsigned char *)dest;
	if (!dst && !src)
		return (0);
	while (i < n)
	{
		dst[i] = str[i];
		i++;
	}
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*src1;
	char	*src2;
	char	*dst;
	size_t	len;

	src1 = (char *)s1;
	src2 = (char *)s2;
	len = (ft_strlen(src1) + ft_strlen(src2));
	dst = malloc(len + 1);
	if (!dst)
		return (0);
	ft_memcpy(dst, src1, ft_strlen(src1));
	ft_memcpy(dst + ft_strlen(src1), src2, ft_strlen(src2) + 1);
	return (dst);
}
