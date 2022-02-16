/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:18:12 by elouisia          #+#    #+#             */
/*   Updated: 2022/02/15 17:48:10 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>

typedef struct s_pipexbonus
{
	char	*path;
	char	**av;
	char	**env;
	char	**tab_path;
}	t_databonus;

int		ft_pipex(int ac, int *file, t_databonus *data);
char	*get_path(char **env);
void	execute_cmd(t_databonus *data, char *cmd);
void	free_tab(char **tab);
int		check_files(int *file, char *av);

#endif