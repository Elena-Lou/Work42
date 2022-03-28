/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 08:34:21 by elouisia          #+#    #+#             */
/*   Updated: 2021/12/30 17:31:34 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	line_len(char *dirty_line)
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

static char	*clean_line(char *dirty_line)
{
	char	*line_to_print;
	int		i;

	line_to_print = malloc(sizeof(char) * (line_len(dirty_line) + 1));
	if (!line_to_print)
		return (NULL);
	i = 0;
	while (dirty_line[i] != '\n' && dirty_line[i] != '\0')
	{
		line_to_print[i] = dirty_line[i];
		i++;
	}
	if (dirty_line[i] == '\n')
	{
		line_to_print[i] = dirty_line[i];
		i++;
	}
	line_to_print[i] = '\0';
	return (line_to_print);
}

static char	*read_line(char *aside, int fd, char *buffer)
{
	int		read_bytes;

	read_bytes = 1;
	if (!aside)
		aside = ft_strdup("");
	while (read_bytes > 0 && ft_strchr(aside, '\n') == 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		buffer[read_bytes] = '\0';
		if (read_bytes == -1 || (read_bytes == 0 && !*aside))
		{
			free(aside);
			aside = NULL;
			return (0);
		}
		aside = ft_strjoin(aside, buffer);
	}
	return (aside);
}

char	*get_next_line(int fd)
{
	static char	*aside;
	char		*dirty_line;
	char		*line_to_print;
	char		buffer[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	if (read(fd, buffer, 0) == -1)
		return (NULL);
	dirty_line = read_line(aside, fd, buffer);
	if (!dirty_line)
		return (NULL);
	line_to_print = clean_line(dirty_line);
	if (!line_to_print)
		return (NULL);
	aside = ft_strdup(&dirty_line[line_len(dirty_line)]);
	free(dirty_line);
	return (line_to_print);
}

// #include <stdio.h>

// int	main(void)
// {
//  	int		fd;
//  	char	*s;

// 	fd = open("line.txt", O_RDONLY);
//  	//fd = 0;
//  	if (fd == -1)
// 	{
// 		printf("Erreur lors de l'execution d'open\n");
// 		return (0);
// 	}
// 	do
// 	{
// 		s = get_next_line(fd);
//  		printf("GNL : %s", s);
// 		free(s);
// 	} while (s != NULL);
//  	close(fd);
//  	return (0);
// }
