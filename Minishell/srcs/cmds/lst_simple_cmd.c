/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_simple_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdubilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 00:20:41 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/22 20:50:56 by jdubilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_cmd	*create_new_token_cmd_ter(char *val, int type, t_struct *rt)
{
	t_token_cmd	*token;
	char		*new_value;

	token = malloc(sizeof(t_token_cmd));
	if (!token)
	{
		ft_lstclear(&rt->list_simpl_cmd, &free_lst_cmd);
		ft_lstclear(&rt->list_cmd_bis, &free_lst_cmd);
		free(rt->line);
		free_double_array(rt->env);
		rl_clear_history();
		ft_printf("minishell: malloc: allocation failed\n");
		exit(1);
	}
	new_value = ft_strdup(val);
	token->value = new_value;
	token->type = type;
	return (token);
}

static t_list	*add_redirection_list(t_list *tmp, t_struct *root)
{
	t_token_cmd	*token;
	t_list		*new;
	char		*value;
	int			type;

	type = ((t_token_cmd *)tmp->content)->type;
	value = ((t_token_cmd *)tmp->next->content)->value;
	token = create_new_token_cmd_ter(value, type, root);
	new = ft_lstnew(token);
	ft_lstadd_back(&root->list_simpl_cmd, new);
	return (tmp->next);
}

static t_list	*join_word(t_list *tmp, t_struct *root, int *free_value)
{
	int			type;
	char		*value;
	t_token_cmd	*token;
	t_list		*new;

	value = NULL;
	type = ((t_token_cmd *)tmp->content)->type;
	if (is_word(tmp) && tmp->next && is_word(tmp->next)
		&& ((t_token_cmd *)tmp->content)->space_after == 0)
	{
		value = ft_strdup(((t_token_cmd *)tmp->content)->value);
		value = return_value(value, tmp);
		tmp = return_tmp(tmp);
		*free_value = 1;
	}
	else
		value = ((t_token_cmd *)tmp->content)->value;
	token = create_new_token_cmd_ter(value, type, root);
	if (*free_value)
		free(value);
	new = ft_lstnew(token);
	ft_lstadd_back(&root->list_simpl_cmd, new);
	return (tmp);
}

void	lst_simple_cmd(t_struct *root)
{
	t_list		*tmp;
	int			free_value;

	tmp = root->list_cmd_bis;
	while (tmp)
	{
		free_value = 0;
		if (is_redirection(tmp) && is_word(tmp->next))
			tmp = add_redirection_list(tmp, root);
		else
			tmp = join_word(tmp, root, &free_value);
		tmp = tmp->next;
	}
}
