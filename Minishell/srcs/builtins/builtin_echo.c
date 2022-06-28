/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:40:08 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/24 16:13:41 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	echo_check_n(char *echo_str)
{
	int	i;

	i = 1;
	if (echo_str[0] != '-')
		return (0);
	else if (echo_str[0] == '-' && echo_str[1] == '\0')
		return (0);
	while (echo_str[i])
	{
		if (echo_str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	check_first_n(char **tab_cmd)
{
	int	j;

	j = 1;
	if (tab_cmd[1][0] == '-')
	{
		if (tab_cmd[1][1] != 'n')
			return (1);
		else
		{
			while (tab_cmd[1] && tab_cmd[1][j])
			{
				if (tab_cmd[1][j] != 'n')
					return (1);
				j++;
			}
		}
	}
	return (0);
}

static int	is_echo_printable(char **tab_cmd)
{
	int	i;

	i = 1;
	while (tab_cmd[i])
	{
		if (!echo_check_n(tab_cmd[i]))
			break ;
		i++;
	}
	return (i);
}

static void	print_echo(char **tab_cmd)
{
	int	i;

	i = is_echo_printable(tab_cmd);
	while (tab_cmd[i])
	{
		if (write(1, tab_cmd[i], ft_strlen(tab_cmd[i])) == -1)
		{
			ft_printf("minishell: echo: write error: %s\n", strerror(errno));
			g_error = 1;
			return ;
		}
		if (tab_cmd[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
}

void	builtin_echo(char **tab_cmd)
{
	g_error = 0;
	if (tab_cmd[1] == NULL)
	{
		if (write(1, "\n", 1) == -1)
		{
			ft_printf("minishell: echo: write error: %s\n", strerror(errno));
			g_error = 1;
			return ;
		}
	}
	else if (tab_cmd[1][0] == '-' && !check_first_n(tab_cmd))
		print_echo(tab_cmd);
	else
	{
		print_echo(tab_cmd);
		write(1, "\n", 1);
	}
}
