/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:18:21 by elouisia          #+#    #+#             */
/*   Updated: 2022/02/18 15:26:11 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	execute_cmd(t_databonus *data, char *cmd)
{
	char	*path_check;
	char	**tab_cmd;
	int		i;

	i = 0;
	tab_cmd = ft_split(cmd, ' ');
	if (access(cmd, F_OK | X_OK) == 0)
		execve(cmd, tab_cmd, data->env);
	else
	{
		while (data->tab_path[i])
		{
			path_check = ft_strjoin(data->tab_path[i], tab_cmd[0]);
			if (access(path_check, F_OK | X_OK) == 0)
				execve(path_check, tab_cmd, data->env);
			free(path_check);
			i++;
		}
	}
	perror("access ");
	free_tab(tab_cmd);
	free_tab(data->tab_path);
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

int	check_files(int *file, char *av)
{
	if (file[0] < 0 || access(av, R_OK) != 0)
	{
		perror("access ");
		close(file[1]);
		return (EXIT_FAILURE);
	}
	else if (file[1] < 0)
	{
		perror("access ");
		close(file[0]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	set_data(char **av, char **env, t_databonus *data, int file[2])
{
	if (!env[0])
		data->path = NULL;
	else
	{
		data->path = get_path(env);
		if (!data->path)
		{
			close(file[1]);
			close(file[0]);
			return ;
		}
		data->tab_path = ft_split(data->path, ':');
	}
	data->av = av;
	data->env = env;
}