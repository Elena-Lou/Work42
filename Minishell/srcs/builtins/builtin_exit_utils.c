/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdubilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 19:48:24 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/24 19:53:58 by jdubilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_error_exit(int ret, int pipe, t_struct *root, char **tab_cmd)
{
	if (pipe == 0 && ret == 2)
	{
		free_all_builtin_exit(root, tab_cmd, pipe);
		exit(g_error);
	}
	else if (pipe == 0 && ret == 3)
	{
		ft_printf("exit\n");
		free_all_builtin_exit(root, tab_cmd, pipe);
		exit(0);
	}
	return (g_error);
}

int	check_error_exit_bis(int pipe, t_struct *root, char **tab_cmd)
{
	if (pipe == 0)
	{
		free_all_builtin_exit(root, tab_cmd, pipe);
		exit(2);
	}
	return (2);
}

void	get_message_builtin_exit(int pipe, int message, char *str)
{
	if (pipe == 0)
		ft_printf("exit\n");
	if (message == 0)
		ft_printf("minishell: exit: %s: numeric argument required\n", str);
	else if (message == 1)
		ft_printf("minishell: exit: too many arguments\n");
}
