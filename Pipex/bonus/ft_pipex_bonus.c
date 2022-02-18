/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:18:17 by elouisia          #+#    #+#             */
/*   Updated: 2022/02/18 17:09:48 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	first_cmds(t_databonus *data, char *cmd)
{
	int		pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
	{	
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		execute_cmd(data, cmd);
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	waitpid(pid, NULL, 0);
	return (EXIT_SUCCESS);
}

static int	last_cmd(t_databonus *data, char *cmd)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		execute_cmd(data, cmd);
	return (EXIT_SUCCESS);
}

int	ft_pipex(int ac, int file[2], t_databonus *data)
{
	int	i;

	i = 2;
	dup2(file[0], STDIN_FILENO);
	while (i < ac - 2)
	{
		first_cmds(data, data->av[i]);
		i++;
	}
	dup2(file[1], STDOUT_FILENO);
	if (i == ac - 1)
		last_cmd(data, data->av[i]);
	close(file[0]);
	close(file[1]);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	int			file[2];
	t_databonus	data;

	if (!env[0])
		return (EXIT_FAILURE);
	if (ac < 5)
	{
		ft_putstr_fd("Usage : ./pipex file1 cmd1 cmd2 file2\n", 1);
		return (EXIT_FAILURE);
	}
	file[0] = open(av[1], O_RDONLY);
	file[1] = open(av[ac - 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (check_files(file, av[1]) != 0)
		return (EXIT_FAILURE);
	set_data(av, env, &data, file);
	ft_pipex(ac, file, &data);
	if (data.path != NULL)
	{
		free(data.path);
		free_tab(data.tab_path);
	}
	return (EXIT_SUCCESS);
}
