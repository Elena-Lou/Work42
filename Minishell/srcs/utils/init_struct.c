/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdubilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 23:18:03 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/24 00:09:30 by jdubilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_env_bis(void)
{
	char	**res;

	res = malloc(sizeof(char *) * 5);
	if (!res)
	{
		ft_printf("minishell: malloc: allocation failed\n");
		exit(1);
	}
	res[0] = ft_strdup("PWD=/mnt/nfs/homes/jdubilla/Projets/minishell");
	res[1] = ft_strdup("PATH=/mnt/nfs/homes/jdubilla/bin:/mnt/nfs/homes/\
jdubilla/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin\
:/bin:/usr/games:/usr/local/games:/snap/bin");
	res[2] = ft_strdup("SHLVL=1");
	res[3] = ft_strdup("_=/usr/bin/env");
	res[4] = NULL;
	return (res);
}

static char	**get_env(char **envp)
{
	char	**res;
	int		i;

	if (!envp[0])
		return (get_env_bis());
	i = 0;
	while (envp[i])
		i++;
	res = malloc(sizeof(char *) * (i + 1));
	if (!res)
	{
		ft_printf("minishell: malloc: allocation failed\n");
		exit(1);
	}
	i = 0;
	while (envp[i])
	{
		res[i] = ft_strdup(envp[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	init_struct(t_struct *root, t_simpl_cmd *simpl_cmd, char **envp)
{
	root->line = NULL;
	root->env = get_env(envp);
	root->ret = 0;
	root->list_token = NULL;
	root->list_cmd = NULL;
	root->list_cmd_bis = NULL;
	root->list_env = NULL;
	root->list_pipe = NULL;
	root->list_simpl_cmd = NULL;
	root->info_simpl_cmd = simpl_cmd;
	root->info_simpl_cmd->filein = 0;
	root->info_simpl_cmd->fileout = 0;
	root->info_simpl_cmd->fd_stdin = -1;
	root->info_simpl_cmd->fd_stdout = -1;
	root->info_simpl_cmd->nbr_here_doc = 0;
	root->info_simpl_cmd->cpy_stdin = 0;
	root->info_simpl_cmd->cpy_stdout = 0;
	root->info_simpl_cmd->err_env = 0;
	root->info_simpl_cmd->is_heredoc = 0;
}

void	clear_struct(t_struct *root, t_simpl_cmd *simpl_cmd)
{
	free(root->line);
	root->line = NULL;
	root->ret = 0;
	root->list_token = NULL;
	root->list_cmd = NULL;
	root->list_pipe = NULL;
	root->list_cmd_bis = NULL;
	root->list_simpl_cmd = NULL;
	root->info_simpl_cmd = simpl_cmd;
	root->info_simpl_cmd->filein = 0;
	root->info_simpl_cmd->fileout = 0;
	root->info_simpl_cmd->fd_stdin = -1;
	root->info_simpl_cmd->fd_stdout = -1;
	root->info_simpl_cmd->nbr_here_doc = 0;
	root->info_simpl_cmd->cpy_stdin = 0;
	root->info_simpl_cmd->cpy_stdout = 0;
	root->info_simpl_cmd->err_env = 0;
	root->info_simpl_cmd->is_heredoc = 0;
}

void	init_struct_pipe(t_token_pipe *infos_pipe, t_list *tmp)
{
	infos_pipe->tab_cmd = NULL;
	infos_pipe->fd_infile = -1;
	infos_pipe->fd_outfile = -1;
	infos_pipe->exec = 1;
	infos_pipe->err = 0;
	infos_pipe->nbr_here_doc = 0;
	while (tmp && ((t_token_cmd *)tmp->content)->type != pipe_c)
	{
		if (((t_token_cmd *)tmp->content)->type == d_chvr_g)
			infos_pipe->nbr_here_doc++;
		tmp = tmp->next;
	}
}
