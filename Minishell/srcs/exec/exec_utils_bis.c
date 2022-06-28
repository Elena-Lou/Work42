/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:31:21 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/27 13:28:47 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	return_error(int num)
{
	(void)num;
	exit(42);
}

void	redirect_and_exec(t_struct *root, char *test_path, char **tab_cmd)
{
	if (root->info_simpl_cmd->filein > 0)
	{
		root->info_simpl_cmd->cpy_stdin = dup(0);
		dup2(root->info_simpl_cmd->fd_stdin, STDIN_FILENO);
	}
	if (root->info_simpl_cmd->fileout > 0)
	{
		root->info_simpl_cmd->cpy_stdout = dup(1);
		dup2(root->info_simpl_cmd->fd_stdout, STDOUT_FILENO);
	}
	signal(SIGQUIT, return_error);
	execve(test_path, tab_cmd, root->env);
}

void	execute_builtin(t_struct *root, char **tab_cmd, int pipe)
{
	if (!ft_strcmp(tab_cmd[0], "echo")
		|| !ft_strcmp(tab_cmd[0], "/usr/bin/echo"))
		builtin_echo(tab_cmd);
	else if (!ft_strcmp(tab_cmd[0], "env")
		|| !ft_strcmp(tab_cmd[0], "/usr/bin/env"))
		builtin_env(root->list_env);
	else if (!ft_strcmp(tab_cmd[0], "pwd")
		|| !ft_strcmp(tab_cmd[0], "/usr/bin/pwd"))
		builtin_pwd(tab_cmd, root->list_env);
	else if (!ft_strcmp(tab_cmd[0], "cd"))
		builtin_cd(tab_cmd, root->list_env);
	else if (!ft_strcmp(tab_cmd[0], "unset"))
		builtin_unset(tab_cmd, &root->list_env);
	else if (!ft_strcmp(tab_cmd[0], "export"))
		builtin_export(tab_cmd, root->list_env);
	else if (!ft_strcmp(tab_cmd[0], "exit"))
		builtin_exit(root, tab_cmd, pipe);
}

void	redirect_and_exec_builtin(t_struct *root, char **tab_cmd, int pipe)
{
	if (root->info_simpl_cmd->filein > 0)
	{
		root->info_simpl_cmd->cpy_stdin = dup(0);
		dup2(root->info_simpl_cmd->fd_stdin, STDIN_FILENO);
	}
	if (root->info_simpl_cmd->fileout > 0)
	{
		root->info_simpl_cmd->cpy_stdout = dup(1);
		dup2(root->info_simpl_cmd->fd_stdout, STDOUT_FILENO);
	}
	execute_builtin(root, tab_cmd, pipe);
}

void	path_error(char **tab_cmd, char **path_split, t_struct *root)
{
	if (tab_cmd[0][0] == '\0')
		ft_printf("Command '' not found\n");
	else if (root->info_simpl_cmd->err_env == 1)
		ft_printf("env: '%s': No such file or directory\n", tab_cmd[0]);
	else
		ft_printf("%s: command not found\n", tab_cmd[0]);
	g_error = 127;
	free_double_array(tab_cmd);
	free_double_array(path_split);
}
