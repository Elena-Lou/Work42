/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:04:05 by elouisia          #+#    #+#             */
/*   Updated: 2021/12/07 16:14:00 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		s_length;
	size_t		start;
	char		*new;

	s_length = ft_strlen(s1);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]) != 0)
		start++;
	while (s_length - 1 > start && ft_strchr(set, s1[s_length - 1]) != 0)
		s_length--;
	new = ft_substr(s1, start, (s_length - start));
	return (new);
}
/*
#include <stdio.h>

int	main()
{
	char s[] = "  hey  ";
	printf("%s\n"ft_strtrim()
}*/