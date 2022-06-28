/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pipe_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 18:30:58 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/27 13:28:16 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_infile_pipe(t_list *tmp, t_token_pipe *inf_pipe, int here_doc)
{
	int		i;
	int		fd;
	char	*value;

	i = 0;
	while (tmp && ((t_token_cmd *)tmp->content)->type != pipe_c)
	{
		if (((t_token_cmd *)tmp->content)->type == chvr_g)
		{
			value = ((t_token_cmd *)tmp->content)->value;
			fd = open(value, O_RDONLY, 00664);
			check_fd_lst_pipe_ter(fd, inf_pipe);
			if (i < here_doc && fd != -1)
				close(fd);
			else if (fd != -1)
			{
				if (inf_pipe->fd_infile != -1)
					close(inf_pipe->fd_infile);
				inf_pipe->fd_infile = fd;
			}
		}
		tmp = tmp->next;
		i++;
	}
}

void	check_outfile_pipe(t_list *tmp, t_token_pipe *inf_pipe)
{
	char	*value;
	int		type;

	while (tmp && ((t_token_cmd *)tmp->content)->type != pipe_c)
	{
		if (((t_token_cmd *)tmp->content)->type == chvr_d
			|| ((t_token_cmd *)tmp->content)->type == d_chvr_d)
		{
			value = ((t_token_cmd *)tmp->content)->value;
			type = ((t_token_cmd *)tmp->content)->type;
			if (inf_pipe->fd_outfile != -1)
				close(inf_pipe->fd_outfile);
			if (type == chvr_d)
				inf_pipe->fd_outfile = open(value, O_WRONLY | O_CREAT
						| O_TRUNC, 00664);
			else if (type == d_chvr_d)
				inf_pipe->fd_outfile = open(value, O_WRONLY | O_CREAT
						| O_APPEND, 00664);
			if (check_fd_lst_pipe(inf_pipe->fd_outfile, value, inf_pipe))
				return ;
		}
		tmp = tmp->next;
	}
}

static void	signal_ctrl_cc(int nb)
{
	(void)nb;
	g_error = -777;
}

static int	wait_good_line_pip(char *limiter, int fd, t_token_pipe *inf_pipe)
{
	char	*str;
	int		i;

	i = 1;
	signal(SIGINT, signal_ctrl_cc);
	while (1)
	{
		str = readline("> ");
		if (check_error_here_doc_pipe(str, i, limiter, inf_pipe))
			return (-20);
		if (str[0] != '\0')
		{
			if (check_finish_here_doc(str, limiter, fd, inf_pipe))
				return (0);
		}
		ft_putstr_fd("\n", fd);
		free(str);
		i++;
	}
	return (0);
}

int	here_doc_pipe(t_list *tmp, t_token_pipe *inf_pipe, int i)
{
	char	*value;
	char	*new_name;
	int		res;

	res = -1;
	while (tmp && ((t_token_cmd *)tmp->content)->type != pipe_c)
	{
		if (((t_token_cmd *)tmp->content)->type == d_chvr_g)
		{
			check_close_fd_pipe(inf_pipe);
			value = ((t_token_cmd *)tmp->content)->value;
			new_name = get_new_name(value, i);
			open_fd_here_doc_pipe(inf_pipe, new_name);
			if (wait_good_line_pip(value, inf_pipe->fd_infile, inf_pipe) == -20
				&& g_error != -13)
			{
				free(new_name);
				return (-20);
			}
			res = open_fd_here_doc_pipe_bis(inf_pipe, new_name, i);
		}
		i++;
		tmp = tmp->next;
	}
	return (res);
}
