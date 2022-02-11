/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:07:42 by elouisia          #+#    #+#             */
/*   Updated: 2021/12/07 12:24:07 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*s1;

	s1 = (char *)s;
	i = (ft_strlen(s1) - 1);
	if ((unsigned char)c == '\0')
		return (&s1[ft_strlen(s)]);
	while (i >= 0)
	{
		if (s1[i] == (unsigned char)c)
			return (&s1[i]);
		i--;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	printf("ma fonction %s\n", ft_strrchr("procrastination", 105));
	printf("fonction de base %s", strrchr("procrastination", 105));
}*/
