/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdubilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:49:28 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/24 19:51:00 by jdubilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_atoll(const char *str, int *err, int pipe)
{
	int			i;
	int			neg;
	long long	nb;

	i = 0;
	neg = 1;
	nb = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((neg == 1 && nb == 922337203685477580 && str[i] > '7')
			|| (neg == -1 && nb == 922337203685477580 && str[i] > '8'))
		{
			*err = 1;
			get_message_builtin_exit(pipe, 0, (char *)str);
			return (0);
		}
		nb = (nb * 10) + (str[i++] - '0');
	}
	return (nb * neg);
}

static int	check_first_arg(char *arg, int pipe)
{
	int	i;

	i = 0;
	if ((arg[0] == '+' || arg[0] == '-') && arg[1])
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			get_message_builtin_exit(pipe, 0, arg);
			g_error = 2;
			return (2);
		}
		i++;
	}
	if ((arg[0] == '+' || arg[0] == '-') && arg[1])
		i--;
	if (i > 19)
	{
		g_error = 2;
		get_message_builtin_exit(pipe, 0, arg);
		return (1);
	}
	return (0);
}

static int	check_args(char **tab_cmd, int pipe)
{
	int	len;
	int	ret;

	len = 0;
	while (tab_cmd[len])
		len++;
	if (len == 1)
		return (3);
	ret = check_first_arg(tab_cmd[1], pipe);
	if (ret)
		return (ret);
	if (len > 2)
	{
		get_message_builtin_exit(pipe, 1, NULL);
		g_error = 1;
		return (1);
	}
	return (0);
}

void	free_all_builtin_exit(t_struct *root, char **tab_cmd, int pipe)
{
	if (pipe == 0)
	{
		free(root->line);
		free_double_array(root->env);
		free_double_array(tab_cmd);
		ft_lstclear(&root->list_simpl_cmd, &free_lst_cmd);
		ft_lstclear(&root->list_cmd_bis, &free_lst_cmd);
		ft_lstclear(&root->list_env, &free_lst_token_env);
		rl_clear_history();
	}
}

int	builtin_exit(t_struct *root, char **tab_cmd, int pipe)
{
	long long	nbr;
	int			err;
	int			ret;

	err = 0;
	ret = check_args(tab_cmd, pipe);
	if (ret)
		return (check_error_exit(ret, pipe, root, tab_cmd));
	if (tab_cmd[1])
	{
		nbr = ft_atoll(tab_cmd[1], &err, pipe);
		if (err == 1)
			return (check_error_exit_bis(pipe, root, tab_cmd));
		while (nbr > 255)
			nbr -= 256;
	}
	else
		nbr = 0;
	free_all_builtin_exit(root, tab_cmd, pipe);
	if (pipe == 0)
	{
		ft_printf("exit\n");
		exit(nbr);
	}
	return (nbr);
}
