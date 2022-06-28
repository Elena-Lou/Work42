/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pipe_utils_bis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdubilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 02:47:42 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/24 21:00:59 by jdubilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_fd_lst_pipe(int fd, char *value, t_token_pipe *inf_pipe)
{
	if (fd == -1)
	{
		if (!access(value, F_OK))
			ft_printf("minishell: %s: Permission denied\n", value);
		else
			ft_printf("minishell: %s: Permission denied\n", value);
		inf_pipe->exec = 0;
		inf_pipe->err = 1;
		g_error = 1;
		return (1);
	}
	return (0);
}

int	check_finish_here_doc(char *str, char *limit, int fd, t_token_pipe *inf_pip)
{
	char	*str_bis;

	str_bis = ft_strcpy_bis(str);
	if (!ft_strcmp(str_bis, limit))
	{
		inf_pip->nbr_here_doc--;
		free(str);
		free(str_bis);
		return (1);
	}
	ft_putstr_fd(str, fd);
	free(str_bis);
	return (0);
}

int	check_error_here_doc_pipe(char *s, int i, char *lim, t_token_pipe *inf_pip)
{
	if (g_error == -777)
	{
		free(s);
		g_error = 130;
		return (1);
	}
	if (s == NULL)
	{
		inf_pip->nbr_here_doc--;
		g_error = -13;
		ft_printf("minishell: warning: here-document at line %d ", i);
		ft_printf("delimited by end-of-file (wanted `%s')\n", lim);
		free(s);
		return (1);
	}
	return (0);
}

char	*get_new_name(char *name, int i)
{
	char	*new_name;
	char	*nb;

	nb = ft_itoa(i);
	new_name = ft_strjoin_qua("/tmp/", name);
	new_name = ft_strjoin_ter(new_name, nb);
	free(nb);
	return (new_name);
}

void	check_close_fd_pipe(t_token_pipe *inf_pipe)
{
	if (inf_pipe->fd_infile != -1)
		close(inf_pipe->fd_infile);
}
