/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 08:34:21 by elouisia          #+#    #+#             */
/*   Updated: 2021/12/20 15:09:12 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	line_len(char *dirty_line)
{
	int	i;

	i = 0;
	if (!dirty_line)
		return (0);
	while (dirty_line[i] != '\n' && dirty_line[i] != '\0')
		i++;
	if (dirty_line[i] == '\n')
		i++;
	return (i);
}

char	*clean_line(char *dirty_line)
{
	char	*line_to_print;
	int		i;

	line_to_print = malloc(sizeof(char) * (line_len(dirty_line) + 1));
	if (!line_to_print)
		return (NULL);
	i = -1;
	while (dirty_line[++i] != '\n' && dirty_line[i] != '\0')
		line_to_print[i] = dirty_line[i];
	if (dirty_line[i] == '\n')
	{
		line_to_print[i] = dirty_line[i];
		i++;
	}
	line_to_print[i] = '\0';
	return (line_to_print);
}

char	*read_line(char *aside, int fd, char *buffer)
{
	int		read_bytes;

	read_bytes = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1000)
		return (NULL);
	while (read_bytes > 0 && ft_strchr(aside, '\n') == 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1 || (read_bytes == 0 && *aside == 0))
		{
			aside = NULL;
			return (0);
		}
		buffer[read_bytes] = '\0';
		aside = ft_strjoin(aside, buffer);
	}
	return (aside);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*aside;
	char		*dirty_line;
	char		*line_to_print;

	if (read(fd, buffer, 0) == -1)
		return (NULL);
	dirty_line = read_line(aside, fd, buffer);
	if (!dirty_line)
		return (NULL);
	aside = &dirty_line[line_len(dirty_line)];
	line_to_print = clean_line(dirty_line);
	if (!line_to_print)
		return (NULL);
	return (line_to_print);
}

#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*s;

	fd = open("line.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Erreur lors de l'execution d'open\n");
		return (0);
	}
	while (s)
	{
		s = get_next_line(fd);
		printf("GNL : %s\n", s);
		free(s);
	} 
	close(fd);
	return (0);
}
