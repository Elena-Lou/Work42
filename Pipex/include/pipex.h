/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 12:17:40 by elouisia          #+#    #+#             */
/*   Updated: 2022/02/15 17:48:03 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>

typedef struct s_pipex
{
	char	*path;
	char	**tab_path;
	char	**av;
	char	**env;
}	t_data;

int		ft_pipex(int *file, t_data *data);
char	*get_path(char **env);
void	execute_cmd(t_data *data, char *cmd);
void	free_tab(char **tab);
int		check_files(int *file, char *av);

#endif