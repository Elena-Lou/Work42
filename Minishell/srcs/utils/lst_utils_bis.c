/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdubilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:51:04 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/24 20:56:56 by jdubilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lst_token(void *content)
{
	t_token	*token;

	token = content;
	free(token);
}

void	free_lst_cmd(void *content)
{
	t_token_cmd	*token;

	token = content;
	free(token->value);
	free(token);
}

void	free_lst_token_env(void *content)
{
	t_token_env	*token;

	token = content;
	free(token->name);
	free(token->value);
	free(token);
}

void	free_lst_pipe(void *content)
{
	t_token_pipe	*token;

	token = content;
	free_double_array(token->tab_cmd);
	free(token);
}

void	add_element(char *new_value, int type, t_struct *root, t_list *tmp)
{
	t_token_cmd	*token;
	t_list		*new;
	int			space;

	space = 0;
	if (((t_token_cmd *)tmp->content)->space_after == 1)
		space = 1;
	token = create_new_token_cmd_bis(new_value, type, space);
	new = ft_lstnew(token);
	ft_lstadd_back(&root->list_cmd_bis, new);
}
