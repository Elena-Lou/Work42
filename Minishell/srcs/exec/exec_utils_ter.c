/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_ter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdubilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 00:46:01 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/27 15:42:49 by jdubilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_struct *root)
{
	if (root->info_simpl_cmd->fileout > 0)
		close (root->info_simpl_cmd->fd_stdout);
	if (root->info_simpl_cmd->filein > 0)
		close (root->info_simpl_cmd->fd_stdin);
}

void	clear_redir(t_struct *root)
{
	if (root->info_simpl_cmd->fileout > 0)
		dup2(root->info_simpl_cmd->cpy_stdout, 1);
	if (root->info_simpl_cmd->filein > 0)
		dup2(root->info_simpl_cmd->cpy_stdin, 0);
}

int	check_dir(char *arg)
{
	int	i;
	int	point;

	i = 0;
	while (arg[i])
	{
		point = 0;
		while (arg[i] == '/')
			i++;
		while (arg[i] == '.')
		{
			i++;
			point++;
			if (point > 2)
				return (0);
		}
		if (arg[i] != '.' && arg[i] != '/')
			return (0);
	}
	return (1);
}

char	*check_envp(t_list *tmp, char **tab_cmd)
{
	while (tmp)
	{
		if (!ft_strcmp(((t_token_env *)tmp->content)->name, "PATH"))
		{
			if (ft_strlen(((t_token_env *)tmp->content)->value) == 0)
				break ;
			return (((t_token_env *)tmp->content)->value);
		}
		tmp = tmp->next;
	}
	ft_printf("minishell: %s: No such file or directory\n", tab_cmd[0]);
	g_error = 127;
	return (NULL);
}

void	execute_cmd_with_path(char **tab_cmd, t_struct *root)
{
	if ((access(tab_cmd[0], W_OK | R_OK) == 0) || check_dir(tab_cmd[0]))
	{
		if (!ft_strcmp(tab_cmd[0], "./minishell"))
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			execute_cmd(root, tab_cmd);
		}
		else
		{
			ft_printf("minishell: %s: Is a directory\n", tab_cmd[0]);
			free_double_array(tab_cmd);
			g_error = 126;
		}
	}
	else
		execute_cmd(root, tab_cmd);
}
