/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 21:26:15 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/27 13:28:00 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_ctrl_cc(int nb)
{
	(void)nb;
	printf ("\n");
}

static void	creat_pipe(t_struct *root)
{
	t_list	*lst_pipe;
	int		**tab_fd;
	int		i;
	int		len_pipe;

	lst_pipe = root->list_pipe;
	i = 0;
	len_pipe = ft_lstsize(lst_pipe);
	tab_fd = malloc(sizeof(int *) * (len_pipe + 1));
	if (!tab_fd)
	{
		free(root->line);
		free_double_array(root->env);
		rl_clear_history();
		ft_printf("minishell: malloc: allocation failed\n");
		exit(1);
	}
	tab_fd[len_pipe] = NULL;
	while (lst_pipe)
	{
		init_pipe(lst_pipe, i, tab_fd);
		lst_pipe = lst_pipe->next;
		i++;
	}
	free_tab_fd(tab_fd);
}

static void	fork_all_cmd(t_struct *root, pid_t *pid)
{
	t_list	*lst_pipe;
	int		i;
	int		len_pipe;

	lst_pipe = root->list_pipe;
	i = 0;
	len_pipe = ft_lstsize(lst_pipe);
	while (i < len_pipe)
	{
		fork_all_cmd_bis(root, lst_pipe, pid, i);
		lst_pipe = lst_pipe->next;
		i++;
	}
}

static void	wait_all_pid(t_struct *root, int *pid)
{
	int	len;
	int	i;
	int	ret_exit;

	len = ft_lstsize(root->list_pipe);
	i = 0;
	while (i < len)
	{
		waitpid(pid[i], &ret_exit, 0);
		if (WIFEXITED(ret_exit))
			g_error = WEXITSTATUS(ret_exit);
		else if (WIFSIGNALED(ret_exit))
			g_error = 128 + WTERMSIG(ret_exit);
		if (g_error == 131 && i + 1 == len)
			ft_printf("Quit (core dumped)\n");
		i++;
	}
}

void	exec_pipe(t_struct *root)
{
	pid_t	*pid;

	signal(SIGINT, signal_ctrl_cc);
	signal(SIGQUIT, SIG_IGN);
	creat_pipe(root);
	pid = malloc(sizeof(pid_t) * ft_lstsize(root->list_pipe));
	if (!pid)
	{
		ft_lstclear(&root->list_pipe, &free_lst_pipe);
		ft_lstclear(&root->list_simpl_cmd, &free_lst_cmd);
		ft_lstclear(&root->list_cmd_bis, &free_lst_cmd);
		free_double_array(root->env);
		rl_clear_history();
		ft_printf("minishell: malloc: allocation failed\n");
		exit(1);
	}
	fork_all_cmd(root, pid);
	wait_all_pid(root, pid);
	free(pid);
}
