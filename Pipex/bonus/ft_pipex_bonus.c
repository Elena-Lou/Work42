/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:18:17 by elouisia          #+#    #+#             */
/*   Updated: 2022/02/17 17:52:56 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	ft_malloc(int ac)
{
	int	i;
	int	**tab_pipe;

	i = 0;
	tab_pipe = malloc(sizeof(int *) * 2);
	if (!tab_pipe)
		return (EXIT_FAILURE);
	while (i < ac - 4)
	{
		tab_pipe[i] = malloc(sizeof(int) * (ac - 4));
		if (!tab_pipe[i])
			return (EXIT_FAILURE);
		i++;
	}
	return (tab_pipe);
}

static int	first_cmds(t_databonus *data, char *cmd, int **fd1, int **fd2)
{
	int		pid;

	if (pipe(fd1) == -1)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd1, STDOUT_FILENO);
		dup2(fd2, STDIN_FILENO);
		execute_cmd(data, cmd);
	}
	close(fd1);
	close(fd2);
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
	int		i;
	int		j;
	int		k;
	int		**pipefd;

	i = 2;
	k = 0;
	pipefd = ft_malloc(ac);
	dup2(file[0], STDIN_FILENO);
	while (i < ac - 1)
	{
		j = 1;
		first_cmds(data, data->av[i], pipefd[k][j], pipefd[k][j - 1]);
		k++;
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

	if (ac < 5)
	{
		ft_putstr_fd("Usage : ./pipex file1 cmd1 cmd2 file2\n", 1);
		return (EXIT_FAILURE);
	}
	if ((access(av[2], F_OK | X_OK) != 0 && !env[0])
		|| (access(av[3], F_OK | X_OK) != 0 && !env[0]))
		return (EXIT_FAILURE);
	file[0] = open(av[1], O_RDONLY);
	file[1] = open(av[4], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (check_files(file, av[1]) != 0)
		return (EXIT_FAILURE);
	set_data(av, env, &data, file);
	ft_pipex(ac, file, &data);
	free(data.path);
	free_tab(data.tab_path);
	return (EXIT_SUCCESS);
}
