/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils_bis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdubilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 21:33:15 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/24 00:59:58 by jdubilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_path_exec(char **path_split, t_struct *root, t_list *tmp, int *pid)
{
	int		i;
	char	**tab_cmd;
	char	*test_path;

	i = 0;
	tab_cmd = ((t_token_pipe *)tmp->content)->tab_cmd;
	while (path_split[i])
	{
		test_path = ft_strjoin_bis(path_split[i], tab_cmd[0]);
		if (*tab_cmd != NULL && access(test_path, F_OK | X_OK) == 0)
		{
			execve(test_path, tab_cmd, root->env);
			g_error = 0;
			return ;
		}
		free(test_path);
		if (path_split[++i] == NULL || tab_cmd[0][0] == '\0')
		{
			free_double_array(path_split);
			path_error_pipe(tab_cmd, root, pid);
			return ;
		}
	}
}

void	close_all_fds(t_list *lst_pipe)
{
	while (lst_pipe)
	{
		if (((t_token_pipe *)lst_pipe->content)->fd_infile != 0)
			close(((t_token_pipe *)lst_pipe->content)->fd_infile);
		if (((t_token_pipe *)lst_pipe->content)->fd_outfile != 1
			&& ((t_token_pipe *)lst_pipe->content)->fd_outfile != -1)
			close(((t_token_pipe *)lst_pipe->content)->fd_outfile);
		lst_pipe = lst_pipe->next;
	}
}

void	path_error_pipe(char **tab_cmd, t_struct *root, int *pid)
{
	if (tab_cmd[0][0] == '\0')
		ft_printf("Command '' not found\n");
	else if (root->info_simpl_cmd->err_env == 1)
		ft_printf("env: '%s': No such file or directory\n", tab_cmd[0]);
	else
		ft_printf("%s: command not found\n", tab_cmd[0]);
	free_all_pipe(root, pid);
	exit(127);
}

void	init_pipe(t_list *lst_pipe, int i, int **tab_fd)
{
	tab_fd[i] = malloc(sizeof(int) * 2);
	if (!tab_fd[i])
	{
		free_tab_fd(tab_fd);
		rl_clear_history();
		ft_printf("minishell: malloc: allocation failed\n");
		exit(1);
	}
	if (pipe(tab_fd[i]) == -1)
		return ;
	if (i == 0 && ((t_token_pipe *)lst_pipe->content)->fd_infile == -1)
		((t_token_pipe *)lst_pipe->content)->fd_infile = 0;
	else if (((t_token_pipe *)lst_pipe->content)->fd_infile == -1)
		((t_token_pipe *)lst_pipe->content)->fd_infile = tab_fd[i - 1][0];
	if (lst_pipe->next == NULL)
	{
		close(tab_fd[i][0]);
		close(tab_fd[i][1]);
		if (i == 0 && ((t_token_pipe *)lst_pipe->content)->fd_outfile == -1)
			((t_token_pipe *)lst_pipe->content)->fd_outfile = 1;
	}
	else if (((t_token_pipe *)lst_pipe->content)->fd_outfile == -1)
		((t_token_pipe *)lst_pipe->content)->fd_outfile = tab_fd[i][1];
}

void	free_all_pipe(t_struct *root, int *pid)
{
	free(pid);
	ft_lstclear(&root->list_pipe, free_lst_pipe);
	ft_lstclear(&root->list_simpl_cmd, free_lst_cmd);
	ft_lstclear(&root->list_cmd_bis, &free_lst_cmd);
	free(root->line);
	free_double_array(root->env);
	ft_lstclear(&root->list_env, &free_lst_token_env);
	rl_clear_history();
}
