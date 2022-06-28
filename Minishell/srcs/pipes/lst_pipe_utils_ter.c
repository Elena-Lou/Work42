/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pipe_utils_ter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 20:52:09 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/27 13:28:11 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nbr_word_cmd_pipe(t_list *tmp)
{
	int		i;

	i = 0;
	while (tmp && ((t_token_cmd *)tmp->content)->type != pipe_c)
	{
		if (is_word(tmp))
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	check_fd_lst_pipe_ter(int fd, t_token_pipe *inf_pipe)
{
	if (fd == -1)
	{
		inf_pipe->exec = 0;
		g_error = 1;
		return (1);
	}
	return (0);
}

int	check_fd_lst_pipe_bis(int fd, char *value)
{
	if (fd == -1)
	{
		if (!access(value, F_OK))
			ft_printf("minishell: %s: Permission denied\n", value);
		else
			ft_printf("minishell: %s: No such file or directory\n", value);
		return (1);
	}
	return (0);
}

void	open_fd_here_doc_pipe(t_token_pipe *inf_pipe, char *new_name)
{
	inf_pipe->fd_infile = open(new_name,
			O_CREAT | O_TRUNC | O_WRONLY, 00664);
}

int	open_fd_here_doc_pipe_bis(t_token_pipe *inf_pip, char *new_name, int i)
{
	close(inf_pip->fd_infile);
	inf_pip->fd_infile = open(new_name, O_RDONLY, 00664);
	free(new_name);
	return (i);
}
