/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_qua.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 20:02:06 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/26 17:57:15 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_qua(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len;
	char	*res;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc(sizeof(*res) * (len + 1));
	if (!res)
		return (NULL);
	if (s1)
	{
		while (s1[i])
			res[j++] = s1[i++];
	}
	i = 0;
	while (s2[i])
		res[j++] = s2[i++];
	res[j] = '\0';
	return (res);
}
