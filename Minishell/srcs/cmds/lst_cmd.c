/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdubilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 21:32:05 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/22 20:37:24 by jdubilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_cmd	*create_new_token_cmd(char *value, int type, t_list *tmp)
{
	t_token_cmd	*token;
	char		*new_value;

	token = malloc(sizeof(t_token_cmd));
	if (!token)
	{
		free(value);
		rl_clear_history();
		ft_printf("minishell: malloc: allocation failed\n");
		exit(1);
	}
	new_value = ft_strdup(value);
	if ((type == d_quot_str || type == s_quot_str) && tmp && tmp->next)
		tmp = tmp->next;
	if (tmp != NULL && ((t_token *)tmp->content)->c == ' ')
		token->space_after = 1;
	else
		token->space_after = 0;
	token->value = new_value;
	token->type = type;
	return (token);
}

static t_list	*join_s_quotes(t_list *tmp, t_struct *root)
{
	int			next_flag;
	int			type;
	char		*input;
	t_token_cmd	*token;
	t_list		*new;

	input = NULL;
	next_flag = ((t_token *)tmp->next->content)->flag;
	while (next_flag != 6)
	{
		tmp = tmp->next;
		input = ft_strjoin(input, ((t_token *)tmp->content)->c);
		next_flag = ((t_token *)tmp->next->content)->flag;
		if (next_flag == 6 || tmp->next == NULL)
		{
			type = s_quot_str;
			token = create_new_token_cmd(input, type, tmp->next);
			new = ft_lstnew(token);
			ft_lstadd_back(&root->list_cmd, new);
			free(input);
			break ;
		}
	}
	tmp = tmp->next;
	return (tmp->next);
}

/* Fonction qui joint les doubles quotes*/
static t_list	*join_d_quotes(t_list *tmp, t_struct *root)
{
	int			next_flag;
	int			type;
	char		*input;
	t_token_cmd	*token;
	t_list		*new;

	input = NULL;
	next_flag = ((t_token *)tmp->next->content)->flag;
	while (next_flag != 5)
	{
		tmp = tmp->next;
		input = ft_strjoin(input, ((t_token *)tmp->content)->c);
		next_flag = ((t_token *)tmp->next->content)->flag;
		if (next_flag == 5 || tmp->next == NULL)
		{
			type = d_quot_str;
			token = create_new_token_cmd(input, type, tmp->next);
			new = ft_lstnew(token);
			ft_lstadd_back(&root->list_cmd, new);
			free(input);
			break ;
		}
	}
	tmp = tmp->next;
	return (tmp->next);
}

static t_list	*join_literal(t_list *tmp, t_struct *root, int flag)
{
	int			next_flag;
	t_token_cmd	*token;
	t_list		*new;
	char		*input;
	int			type;

	input = NULL;
	next_flag = ((t_token *)tmp->content)->flag;
	while (flag == next_flag)
	{
		input = ft_strjoin(input, ((t_token *)tmp->content)->c);
		if (tmp->next == NULL)
			break ;
		next_flag = ((t_token *)tmp->next->content)->flag;
		tmp = tmp->next;
	}
	type = get_type(input);
	token = create_new_token_cmd(input, type, tmp);
	new = ft_lstnew(token);
	ft_lstadd_back(&root->list_cmd, new);
	free(input);
	return (tmp);
}

void	join_token(t_struct *root, t_list *tmp)
{
	int		flag;

	while (1)
	{
		while (((t_token *)tmp->content)->c == ' ' && tmp->next != NULL)
			tmp = tmp->next;
		if (tmp->next == NULL)
			return ;
		flag = ((t_token *)tmp->content)->flag;
		if (flag == 5 && tmp->next
			&& ((t_token *)tmp->next->content)->flag == 5)
			tmp = add_void_token(tmp, root, flag);
		else if (flag == 6 && tmp->next
			&& ((t_token *)tmp->next->content)->flag == 6)
			tmp = add_void_token(tmp, root, flag);
		else if (flag == 5)
			tmp = join_d_quotes(tmp, root);
		else if (flag == 6)
			tmp = join_s_quotes(tmp, root);
		else
			tmp = join_literal(tmp, root, flag);
		if (tmp->next == NULL || !tmp)
			return ;
	}
}
