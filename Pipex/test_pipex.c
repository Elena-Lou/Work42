/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 12:17:34 by elouisia          #+#    #+#             */
/*   Updated: 2022/02/04 15:48:59 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/pipex.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
/*
int main() {
	int fd1[2];
	int fd2[2];
	char *end_string = "forgeeks.org";
	char input_string[100];
	pid_t p;
	
	if (pipe(fd1) == -1 || pipe(fd2) == -1)
	{
	    fprintf(stderr, "Pipe Failed");
	    return (1);
	}
	scanf("%s", input_string);
	p = fork();
	if (p < 0)
	{
	    fprintf(stderr, "fork failed");
	    return (1);
	}
	// Parent
	else if (p > 0)
	{
	    char concat_string[100];
	    
	    close(fd1[0]);
	    write(fd1[1], input_string, strlen(input_string) + 1);
	    close(fd1[1]);
	    wait(NULL);
	    close(fd2[1]);
	    read(fd2[0], concat_string, 100);
	    printf("%s\n", concat_string);
	    close(fd2[0]);
	}
	
	else
	{
	    close(fd1[1]);
	    char concat_string[100];
	    read(fd1[0], concat_string, 100);
	    int k = strlen(concat_string);
	    int i;
	    for (i = 0; i < strlen(end_string); i++)
	        concat_string[k++] = end_string[i];
	    concat_string[k] = '\0';
	    close(fd1[0]);
	    close (fd2[0]);
	    write(fd2[1], concat_string, strlen(concat_string) + 1);
	    close(fd2[1]);
	    
	    exit(0);
	}
	return 0;
}*/
/*
int	main(void)
{
   pid_t pid = fork();

	if (pid < 0)
	{
		fprintf(stderr, "Fork Failed");
		return (1);
	}
	else if (pid == 0)
		printf("I'm the child \n");
	else
	{
		printf("I wait for the child\n");
		wait(NULL);
		printf("Child Complete \n");
	}
	return (0);
}
*/
/*
# pipeEnds[0] gets the read end; pipeEnds[1] gets the write end.
int pipeEnds[2];

pipe(pipeEnds);

int returnCode = fork();

if (returnCode == 0) {

  # Don't need a loopback.
  close(pipeEnds[1]);

  # Read some data from the pipe.
  char data[14];
  read(pipeEnds[0], data, 14);
} else {

  # Don't need a loopback.
  close(pipeEnds[0]);

  # Write some data to the pipe.
  write(pipeEnds[1], "Hello, sweet child!\n", 14);
}
*/
/*
int	main(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		printf("I am the eldest\n");
	}
	else
	{
		wait(NULL);
		printf("I am the parent\n");
	}
	return (0);
}
*/
/*
int	main(int ac, char **av)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (pipe(fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (3);
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "rtt", NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}*/
/*
int	main(void)
{
	int	pipefd[2];
	int childPid;

	pipe(pipefd);
	childPid = fork();
	if (childPid == 0) {
		char *av[] = {
			"/bin/echo",
			"h_e_l_l_o_ _w_o_r_l_d",
			NULL,
		};
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		if (execv(av[0], av) == -1)
			perror("execv: ");
		exit(0);
	}
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
	return (0);
}
*/
