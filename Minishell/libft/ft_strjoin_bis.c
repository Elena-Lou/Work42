/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdubilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:33:35 by jdubilla          #+#    #+#             */
/*   Updated: 2021/11/30 17:48:57 by jdubilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_bis(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	j = -1;
	len = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc(sizeof(*res) * (len + 2));
	if (!res)
		return (NULL);
	while (s1[++i])
		res[++j] = s1[i];
	i = -1;
	res[++j] = '/';
	while (s2[++i])
		res[++j] = s2[i];
	j++;
	res[j] = '\0';
	return (res);
}
