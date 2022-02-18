/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:02:27 by elouisia          #+#    #+#             */
/*   Updated: 2022/02/18 14:56:03 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	first_child(int pipefd[2], int infile, t_data *data)
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	execute_cmd(data, data->av[2]);
	close(pipefd[1]);
	close(infile);
	exit(0);
}

static int	second_child(int pipefd[2], int outfile, t_data *data)
{
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	execute_cmd(data, data->av[3]);
	close(pipefd[0]);
	close(outfile);
	exit(0);
}

int	ft_pipex(int file[2], t_data *data)
{
	int		pipefd[2];
	int		pid1;
	int		pid2;
	int		status;

	if (pipe(pipefd) == -1)
		return (EXIT_FAILURE);
	pid1 = fork();
	if (pid1 < 0)
		return (EXIT_FAILURE);
	if (pid1 == 0)
		first_child(pipefd, file[0], data);
	pid2 = fork();
	if (pid2 < 0)
		return (EXIT_FAILURE);
	if (pid2 == 0)
		second_child(pipefd, file[1], data);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	int		file[2];
	t_data	data;

	if (ac != 5)
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
	ft_pipex(file, &data);
	if (data.path != NULL)
	{
		free(data.path);
		free_tab(data.tab_path);
	}
	return (EXIT_SUCCESS);
}
