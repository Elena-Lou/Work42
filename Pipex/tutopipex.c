/*#include "pipex.h"

int	ft_pipex(char *av, char **env)
{
	int		pipefd[2];
	int		pid1, pid2;
	int		i, j;
	char	*path;

	i = 0;
	j = 5;
	if (pipe(pipefd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
	{
		char *av[] = {
			"/bin/echo",
			"h_e_l_l_o_ _w_o_r_l_d",
			NULL
		};
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		if (execv(av[0], av) == -1)
			perror("execv: ");
		exit(0);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (3);
	if (pid2 == 0)
	{
		char *av[] = {
		"/usr/bin/tr",
		"-d",
		"_",
		NULL,
		};
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		if (execv(av[0], av) == -1)
			perror("execv : ");
		exit(0);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	if (!envp[0])
		return (0);
	if (ac != 5)
	{
		printf("Usage : ./pipex file1 cmd1 cmd2 file2\n");
		return (0);
	}
	ft_pipex(av[2], envp);
	return (0);
}
*/