/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:02:27 by elouisia          #+#    #+#             */
/*   Updated: 2022/02/11 16:43:21 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	first_child(int pipefd[2], char **env, char **av, int infile)
{
	char	*path;

	path = get_path(env);
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	check_path(av[2], path, env);
	close(pipefd[1]);
	close(infile);
	free(path);
	exit(0);
}

static int	second_child(int pipefd[2], char **env, char **av, int outfile)
{
	char	*path;

	path = get_path(env);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	check_path(av[3], path, env);
	close(pipefd[0]);
	close(outfile);
	free(path);
	exit(0);
}

int	ft_pipex(char **av, char **env, int infile, int outfile)
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
		first_child(pipefd, env, av, infile);
	pid2 = fork();
	if (pid2 < 0)
		return (EXIT_FAILURE);
	if (pid2 == 0)
		second_child(pipefd, env, av, outfile);
	waitpid(-1, &status, 0);
	close(pipefd[0]);
	close(pipefd[1]);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av, char **envp)
{
	int	infile;
	int	outfile;

	if (!envp[0])
		return (0);
	if (ac != 5)
	{
		ft_putstr_fd("Usage : ./pipex file1 cmd1 cmd2 file2\n", 1);
		return (EXIT_FAILURE);
	}
	infile = open(av[1], O_RDONLY);
	if (infile == -1)
		return (EXIT_FAILURE);
	outfile = open(av[4], O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (outfile == -1)
		return (EXIT_FAILURE);
	ft_pipex(av, envp, infile, outfile);
	return (EXIT_SUCCESS);
}
