/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:28:19 by elouisia          #+#    #+#             */
/*   Updated: 2022/02/11 14:41:02 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char **env)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	j = 5;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5) != 0)
			path = ft_strdup(&env[i][j]);
		i++;
	}
	return (path);
}

void	check_path(char *cmd, char *path, char **env)
{
	char	**tab_path;
	char	*path_check;
	char	**tab_cmd;
	int		i;

	i = 0;
	if (!path)
		return ;
	tab_path = ft_split(path, ':');
	tab_cmd = ft_split(cmd, ' ');
	while (tab_path[i])
	{
		path_check = ft_strjoin(tab_path[i], tab_cmd[0]);
		if (access(path_check, F_OK | X_OK) == 0)
		{
			execve(path_check, tab_cmd, env);
			perror("execve : ");
			free(path_check);
			free_tab(tab_cmd);
		}
		free(path_check);
		i++;
	}
	free_tab(tab_cmd);
	free_tab(tab_path);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	while (i > 0)
	{
		free(tab[i - 1]);
		i--;
	}
	free(tab);
}
