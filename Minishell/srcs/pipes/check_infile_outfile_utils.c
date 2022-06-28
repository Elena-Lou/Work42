/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_infile_outfile_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 20:42:10 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/27 13:27:35 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_outfile(int type, char *value, t_struct *root)
{
	if (root->info_simpl_cmd->fileout > 0)
		close(root->info_simpl_cmd->fd_stdout);
	if (type == chvr_d)
		root->info_simpl_cmd->fd_stdout = open(value, O_WRONLY | O_CREAT
				| O_TRUNC, 00664);
	else if (type == d_chvr_d)
		root->info_simpl_cmd->fd_stdout = open(value, O_WRONLY | O_CREAT
				| O_APPEND, 00664);
}

void	check_infile_bis(t_struct *root, int i, int fd, int pos_here_doc)
{
	if (i < pos_here_doc)
		close(fd);
	else
	{
		if (root->info_simpl_cmd->fd_stdin != -1)
			close(root->info_simpl_cmd->fd_stdin);
		root->info_simpl_cmd->fd_stdin = fd;
	}
	root->info_simpl_cmd->filein++;
}

void	open_fd_here_doc(t_struct *root)
{
	close(root->info_simpl_cmd->fd_stdin);
	root->info_simpl_cmd->fd_stdin = open("/tmp/tmp_file",
			O_RDONLY, 00664);
}

void	message_check_infile(char *value)
{
	if (!access(value, F_OK))
		ft_printf("minishell: %s: Permission denied\n", value);
	else
		ft_printf("minishell: %s: No such file or directory\n", value);
}
