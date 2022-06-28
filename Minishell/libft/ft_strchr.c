/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:23:44 by elouisia          #+#    #+#             */
/*   Updated: 2022/03/28 15:48:46 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*s1;

	i = 0;
	s1 = (char *)s;
	if ((unsigned char)c == '\0')
		return (&s1[ft_strlen(s)]);
	while (s1[i])
	{
		if (s1[i] == (unsigned char) c)
			return (&s1[i]);
		i++;
	}
	return (0);
}
