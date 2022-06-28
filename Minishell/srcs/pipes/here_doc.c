/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 18:55:01 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/27 13:28:06 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcpy_bis(char *str)
{
	int		i;
	char	*res;

	i = 0;
	res = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!res)
	{
		free(str);
		rl_clear_history();
		ft_printf("minishell: malloc: allocation failed\n");
		exit(1);
	}
	while (str[i] != '\0')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static void	signal_ctrl_cc(int nb)
{
	(void)nb;
	g_error = -777;
}

static int	check_error_here_doc(char *str, int *ret, int i, char *limiter)
{
	if (g_error == -777)
	{
		free (str);
		*ret = 2;
		g_error = 130;
		return (1);
	}
	if (str == NULL)
	{
		ft_printf("minishell: warning: here-document at line %d\
delimited by end-of-file (wanted `%s')\n", i, limiter);
		free (str);
		*ret = 1;
		g_error = 0;
		return (1);
	}
	return (0);
}

static int	finish_or_add_line(char *str, int fd, char *limiter, t_struct *root)
{
	char	*str_bis;

	str_bis = ft_strcpy_bis(str);
	if (!ft_strcmp(str_bis, limiter))
	{
		root->info_simpl_cmd->nbr_here_doc--;
		free(str);
		free(str_bis);
		return (1);
	}
	ft_putstr_fd(str, fd);
	free(str_bis);
	return (0);
}

void	wait_good_line(char *limiter, int fd, int *ret, t_struct *root)
{
	char	*str;
	int		i;

	i = 1;
	*ret = 0;
	signal(SIGINT, signal_ctrl_cc);
	while (1)
	{
		str = readline("> ");
		if (check_error_here_doc(str, ret, i, limiter))
		{
			root->info_simpl_cmd->nbr_here_doc--;
			return ;
		}
		if (str[0] != '\0')
		{
			if (finish_or_add_line(str, fd, limiter, root))
				return ;
		}
		ft_putstr_fd("\n", fd);
		free (str);
		i++;
	}
}
