/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:41:53 by elouisia          #+#    #+#             */
/*   Updated: 2022/03/03 15:17:48 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
