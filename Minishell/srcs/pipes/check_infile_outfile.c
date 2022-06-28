/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_infile_outfile.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 00:22:37 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/27 13:27:41 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_outfile(t_struct *root, t_list *tmp)
{
	int		type;
	char	*value;

	while (tmp)
	{
		type = ((t_token_cmd *)tmp->content)->type;
		if (type == chvr_d || type == d_chvr_d)
		{
			value = ((t_token_cmd *)tmp->content)->value;
			open_outfile(type, value, root);
			if (root->info_simpl_cmd->fd_stdout == -1)
			{
				ft_printf("minishell: %s: Permission denied\n", value);
				g_error = 1;
				return (1);
			}
			root->info_simpl_cmd->fileout++;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	open_here_doc(t_list *tmp, t_struct *root, int i, int ret)
{
	int	ret_here_doc;

	ret_here_doc = 0;
	while (tmp)
	{
		if (((t_token_cmd *)tmp->content)->type == d_chvr_g)
		{
			ret = i;
			root->info_simpl_cmd->fd_stdin = open("/tmp/tmp_file",
					O_CREAT | O_TRUNC | O_WRONLY, 00664);
			if (check_return_fd(root->info_simpl_cmd->fd_stdin))
				return (-1);
			wait_good_line(((t_token_cmd *)tmp->content)->value,
				root->info_simpl_cmd->fd_stdin, &ret_here_doc, root);
			open_fd_here_doc(root);
			if ((ret_here_doc == 1 && root->info_simpl_cmd->nbr_here_doc == 0)
				|| ret_here_doc == 2)
				return (-5);
			root->info_simpl_cmd->filein++;
		}
		tmp = tmp->next;
		i++;
	}
	return (ret);
}

int	check_infile(t_list *tmp, t_struct *root, int pos_here_doc)
{
	int		i;
	int		fd;
	char	*value;

	i = 0;
	while (tmp)
	{
		if (((t_token_cmd *)tmp->content)->type == chvr_g)
		{
			value = ((t_token_cmd *)tmp->content)->value;
			fd = open(value, O_RDONLY, 00664);
			if (fd == -1)
			{
				message_check_infile(value);
				g_error = 1;
				return (-5);
			}
			check_infile_bis(root, i, fd, pos_here_doc);
		}
		i++;
		tmp = tmp->next;
	}
	return (0);
}

void	nbr_here_doc(t_struct *root)
{
	t_list	*tmp;

	tmp = root->list_simpl_cmd;
	while (tmp)
	{
		if (((t_token_cmd *)tmp->content)->type == d_chvr_g)
			root->info_simpl_cmd->nbr_here_doc++;
		tmp = tmp->next;
	}
}

int	check_infile_outfile(t_struct *root)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = root->list_simpl_cmd;
	nbr_here_doc(root);
	i = open_here_doc(tmp, root, 0, -1);
	if (i == -5)
		return (1);
	if (check_infile(tmp, root, i) == -5)
	{
		check_outfile(root, tmp);
		return (1);
	}
	if (check_outfile(root, tmp))
		return (1);
	return (0);
}
