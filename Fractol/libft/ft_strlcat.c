/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:56:17 by elouisia          #+#    #+#             */
/*   Updated: 2021/11/30 14:26:12 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	s_length;
	size_t	d_length;

	s_length = ft_strlen(src);
	d_length = ft_strlen(dst);
	if (!size || d_length >= size)
		return (size + s_length);
	ft_strlcpy(&dst[d_length], src, (size - d_length));
	return (d_length + s_length);
}
