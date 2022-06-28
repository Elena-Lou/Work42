/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 21:30:33 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/27 13:27:51 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_builtin_pipe(char *cmd, t_struct *rot, pid_t *pid, t_list *tmp)
{
	char	**tab_cmd;

	tab_cmd = ((t_token_pipe *)tmp->content)->tab_cmd;
	if (!ft_strcmp(cmd, "exit"))
	{
		g_error = builtin_exit(rot, tab_cmd, 1);
		free_all_pipe(rot, pid);
		exit(g_error);
	}
	execute_builtin(rot, ((t_token_pipe *)tmp->content)->tab_cmd, 1);
	free_all_pipe(rot, pid);
	exit(0);
}

static void	pipe_with_path(char *cmd, t_struct *root, pid_t *pid, t_list *tmp)
{
	if ((access(cmd, W_OK | R_OK) == 0) || check_dir(cmd))
	{
		ft_printf("minishell: %s: Is a directory\n", cmd);
		free_all_pipe(root, pid);
		g_error = 126;
		exit(0);
	}
	else
	{
		signal(SIGQUIT, return_error_pipe);
		execve(cmd, ((t_token_pipe *)tmp->content)->tab_cmd, root->env);
	}
}

static void	exec_pipe_without_path(t_struct *root, t_list *lst_pipe, pid_t *pid)
{
	char	*path_env;
	char	**path_split;
	char	**tab_cmd;

	tab_cmd = ((t_token_pipe *)lst_pipe->content)->tab_cmd;
	path_env = check_envp(root->list_env, tab_cmd);
	path_split = ft_split(path_env, ':');
	test_path_exec(path_split, root, lst_pipe, pid);
}

static void	exec_cmd_pipe(t_struct *root, t_list *lst_pipe, pid_t *pid)
{
	char	*cmd;

	if (((t_token_pipe *)lst_pipe->content)->exec != 1)
	{
		free_all_pipe(root, pid);
		exit(0);
	}
	dup2(((t_token_pipe *)lst_pipe->content)->fd_infile, STDIN_FILENO);
	dup2(((t_token_pipe *)lst_pipe->content)->fd_outfile, STDOUT_FILENO);
	close_all_fds(root->list_pipe);
	if (((t_token_pipe *)lst_pipe->content)->exec == 1)
	{
		cmd = ((t_token_pipe *)lst_pipe->content)->tab_cmd[0];
		if (is_builtin(cmd))
			exec_builtin_pipe(cmd, root, pid, lst_pipe);
		else if ((access(cmd, F_OK | X_OK) == 0))
			pipe_with_path(cmd, root, pid, lst_pipe);
		else
			exec_pipe_without_path(root, lst_pipe, pid);
	}
}

void	fork_all_cmd_bis(t_struct *root, t_list *lst_pipe, pid_t *pid, int i)
{
	pid[i] = fork();
	if (pid[i] == -1)
		exit(1);
	if (pid[i] == 0)
		exec_cmd_pipe(root, lst_pipe, pid);
	if (((t_token_pipe *)lst_pipe->content)->fd_infile != 0)
		close(((t_token_pipe *)lst_pipe->content)->fd_infile);
	if (((t_token_pipe *)lst_pipe->content)->fd_outfile != 1
		&& ((t_token_pipe *)lst_pipe->content)->fd_outfile != -1)
		close(((t_token_pipe *)lst_pipe->content)->fd_outfile);
}
