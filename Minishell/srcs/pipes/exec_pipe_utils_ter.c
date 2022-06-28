/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils_ter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdubilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 21:36:18 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/24 00:18:21 by jdubilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab_fd(int **tab_fd)
{
	int	i;

	i = 0;
	while (tab_fd[i])
	{
		free(tab_fd[i]);
		i++;
	}
	free(tab_fd);
}

void	return_error_pipe(int nb)
{
	(void)nb;
	exit(42);
}

void	free_tab_exec_cmd_pipe(char *test_path, char **path_splt)
{
	free(test_path);
	free_double_array(path_splt);
}
