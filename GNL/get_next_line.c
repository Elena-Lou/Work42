/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 08:34:21 by elouisia          #+#    #+#             */
/*   Updated: 2021/12/13 14:10:55 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	int		ret;
	char	buf[BUFFER_SIZE + 1];
	char	*line;

	line = malloc(BUFFER_SIZE);
	while (ret = read(fd, buf, BUFFER_SIZE))
	{
		buf[ret] = '\0';
		line = ft_strjoin(line, buf);
//		printf("Here\n");
		if (ft_memchr(buf, '\n', ret) != 0)
		{
//			printf("And here\n");
			break ;
		}
	}
//	ft_putstr_fd(line, 1);
	return (line);
}

int	main(void)
{
	int fd;
	char *s;
	
	fd = open("line.txt", O_RDONLY);
	s = get_next_line(fd);
	ft_putstr_fd(s,1);
	return (0);
}