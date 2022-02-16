/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:18:17 by elouisia          #+#    #+#             */
/*   Updated: 2022/02/16 17:28:24 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	first_child(int pipefd[2], int infile, t_databonus *data, char *cmd)
{
	dup2(pipefd[1], STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	if (pid == 0)
		execute_cmd(data, cmd);
	waitpid(pid, NULL, 0);
	close(pipefd[1]);
	close(pipefd[0]);
	close(infile);
	return (EXIT_SUCCESS);
}

static int	second_child(int outfile, t_databonus *data, char *cmd)
{
	int	pipefd[2];

	close(pipefd[1]);
	dup2(outfile, STDOUT_FILENO);
	execute_cmd(data, cmd);
	close(pipefd[0]);
	close(outfile);
	return (EXIT_SUCCESS);
}

int	ft_pipex(int ac, int file[2], t_databonus *data)
{
	int		i;
	int		pid1;
	int		pid2;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (EXIT_FAILURE);
	pid1 = fork();
	i = 2;
	dup2(file[0], STDIN_FILENO);
	while (i < ac - 1)
	{
		first_child(pipefdfile[0], data, data->av[i]);
		i++;
	}
	if (i == ac - 2)
		second_child(file[1], data, data->av[i]);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av, char **envp)
{
	int			file[2];
	t_databonus	data;

	if (ac < 5)
	{
		ft_putstr_fd("Usage : ./pipex file1 cmd1 cmd2 file2\n", 1);
		return (EXIT_FAILURE);
	}
	if ((access(av[2], F_OK | X_OK) != 0 && !envp[0])
		|| (access(av[3], F_OK | X_OK) != 0 && !envp[0]))
		return (EXIT_FAILURE);
	file[0] = open(av[1], O_RDONLY);
	file[1] = open(av[4], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (check_files(file, av[1]) != 0)
		return (EXIT_FAILURE);
	data.path = get_path(envp);
	if (!data.path)
		return (EXIT_FAILURE);
	data.av = av;
	data.env = envp;
	data.tab_path = ft_split(data.path, ':');
	ft_pipex(ac, file, &data);
	free(data.path);
	free_tab(data.tab_path);
	return (EXIT_SUCCESS);
}
