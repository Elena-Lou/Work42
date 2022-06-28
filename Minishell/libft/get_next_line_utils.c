/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 08:34:07 by elouisia          #+#    #+#             */
/*   Updated: 2022/04/25 19:10:01 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr_gnl(char *s, int c)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	if ((unsigned char)c == '\0')
		return (&s[ft_strlen_gnl(s)]);
	while (s[i])
	{
		if (s[i] == (unsigned char) c)
			return (&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup_gnl(char *src)
{
	int		i;
	char	*dest;

	i = 0;
	while (src[i])
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	dest = malloc(sizeof(char) * (ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1));
	if (!dest)
		return (NULL);
	while (s1[i])
		dest[j++] = s1[i++];
	i = 0;
	while (s2[i])
	{
		dest[j + i] = s2[i];
		i++;
	}
	free(s1);
	dest[j + i] = '\0';
	return (dest);
}
