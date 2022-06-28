/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 18:30:56 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/27 13:28:22 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	word_to_tab_pipe(t_list *tmp, t_token_pipe *inf_pipe, int nbr_word)
{
	char	*value;
	int		i;

	i = 0;
	if (!nbr_word)
		return ;
	if (!inf_pipe->tab_cmd)
	{
		rl_clear_history();
		ft_printf("minishell: malloc: allocation failed\n");
		exit(1);
	}
	while (i < nbr_word)
	{
		if (is_word(tmp))
		{
			value = ((t_token_cmd *)tmp->content)->value;
			inf_pipe->tab_cmd[i] = ft_strdup(value);
			i++;
		}
		tmp = tmp->next;
	}
	inf_pipe->tab_cmd[i] = NULL;
}

static t_token_pipe	*create_new_token_pipe(t_token_pipe *inf_pipe, t_struct *rt)
{
	t_token_pipe	*token;

	token = malloc(sizeof(t_token_pipe));
	if (!token)
	{
		ft_lstclear(&rt->list_pipe, &free_lst_pipe);
		ft_lstclear(&rt->list_simpl_cmd, &free_lst_cmd);
		ft_lstclear(&rt->list_cmd_bis, &free_lst_cmd);
		free_double_array(rt->env);
		rl_clear_history();
		ft_printf("minishell: malloc: allocation failed\n");
		exit(1);
	}
	token->tab_cmd = inf_pipe->tab_cmd;
	token->fd_infile = inf_pipe->fd_infile;
	token->fd_outfile = inf_pipe->fd_outfile;
	token->exec = inf_pipe->exec;
	token->err = inf_pipe->err;
	return (token);
}

static t_list	*get_infos_pipe(t_list *tmp, t_struct *root, int *err, int i)
{
	t_token_pipe	infos_pipe;
	t_token_pipe	*token;
	t_list			*new;

	init_struct_pipe(&infos_pipe, tmp);
	i = here_doc_pipe(tmp, &infos_pipe, 0);
	if (i == -20)
	{
		*err = -1;
		return (NULL);
	}
	check_infile_pipe(tmp, &infos_pipe, i);
	check_outfile_pipe(tmp, &infos_pipe);
	i = nbr_word_cmd_pipe(tmp);
	if (i == 0)
		infos_pipe.exec = 0;
	else
		infos_pipe.tab_cmd = malloc(sizeof(char *) * (i + 1));
	word_to_tab_pipe(tmp, &infos_pipe, i);
	token = create_new_token_pipe(&infos_pipe, root);
	new = ft_lstnew(token);
	ft_lstadd_back(&root->list_pipe, new);
	while (tmp && ((t_token_cmd *)tmp->content)->type != pipe_c)
		tmp = tmp->next;
	return (tmp);
}

static void	check_all_infile(t_list *tmp)
{
	int		fd;
	char	*value;

	while (tmp)
	{
		if (((t_token_cmd *)tmp->content)->type == chvr_g)
		{
			value = ((t_token_cmd *)tmp->content)->value;
			fd = open(value, O_RDONLY, 00664);
			check_fd_lst_pipe_bis(fd, value);
		}
		tmp = tmp->next;
	}
}

int	lst_pipe(t_struct *root)
{
	t_list	*tmp;
	int		err;

	err = 0;
	tmp = root->list_simpl_cmd;
	check_all_infile(tmp);
	while (tmp)
	{
		tmp = get_infos_pipe(tmp, root, &err, 0);
		if (tmp && tmp->next)
			tmp = tmp->next;
		if (err == -1)
			return (1);
	}
	return (0);
}
