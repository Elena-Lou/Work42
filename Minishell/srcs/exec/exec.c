/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdubilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 18:37:09 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/27 15:34:14 by jdubilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_cmd_bis(char **tab_cmd, char **path_split, t_struct *root)
{
	int		i;
	pid_t	pid;
	char	*test_path;

	i = 0;
	while (path_split[i])
	{
		test_path = ft_strjoin_bis(path_split[i], tab_cmd[0]);
		if (*tab_cmd != NULL && access(test_path, F_OK | X_OK) == 0)
		{
			pid = fork();
			if (pid == 0)
				redirect_and_exec(root, test_path, tab_cmd);
			get_exit_status(root, pid);
			free_tab_exec_cmd(test_path, tab_cmd, path_split);
			return ;
		}
		free(test_path);
		if (path_split[++i] == NULL || tab_cmd[0][0] == '\0')
		{
			path_error(tab_cmd, path_split, root);
			return ;
		}
	}
}

void	execute_cmd(t_struct *root, char **tab_cmd)
{
	pid_t	pid;
	int		ret_exit;

	pid = fork();
	if (pid == 0)
		redirect_and_exec(root, tab_cmd[0], tab_cmd);
	waitpid(pid, &ret_exit, 0);
	if (WIFEXITED(ret_exit))
		g_error = WEXITSTATUS(ret_exit);
	else if (WIFSIGNALED(ret_exit))
		g_error = 128 + WTERMSIG(ret_exit);
	if (g_error == 131)
		ft_printf("Quit (core dumped)\n");
	close_fds(root);
	free_double_array(tab_cmd);
}

static void	exec_builtin(t_struct *root, char **tab_cmd, int pipe)
{
	redirect_and_exec_builtin(root, tab_cmd, pipe);
	clear_redir(root);
	close_fds(root);
	free_double_array(tab_cmd);
}

static void	signal_ctrl_cc(int nb)
{
	(void)nb;
	printf("\n");
}

void	exec_simple_cmd(t_struct *root)
{
	int		nbr_word;
	char	**tab_cmd;
	char	*path_env;
	char	**path_split;

	signal(SIGINT, signal_ctrl_cc);
	nbr_word = nbr_word_cmd(root);
	if (nbr_word == 0)
		return ;
	tab_cmd = word_to_tab(nbr_word, root->list_simpl_cmd, root);
	if (is_builtin(tab_cmd[0]))
		exec_builtin(root, tab_cmd, 0);
	else if ((access(tab_cmd[0], F_OK | X_OK) == 0))
		execute_cmd_with_path(tab_cmd, root);
	else
	{
		path_env = check_envp(root->list_env, tab_cmd);
		if (!path_env)
		{
			free_double_array(tab_cmd);
			return ;
		}
		path_split = ft_split(path_env, ':');
		execute_cmd_bis(tab_cmd, path_split, root);
	}
}
