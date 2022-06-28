/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_qua.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 01:21:18 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/27 13:28:42 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_exit_status(t_struct *root, pid_t pid)
{
	int	ret_exit;

	waitpid(pid, &ret_exit, 0);
	if (WIFEXITED(ret_exit))
		g_error = WEXITSTATUS(ret_exit);
	else if (WIFSIGNALED(ret_exit))
		g_error = 128 + WTERMSIG(ret_exit);
	if (g_error == 131)
		ft_printf("Quit (core dumped)\n");
	close_fds(root);
}
