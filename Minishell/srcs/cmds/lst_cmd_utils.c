/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:07:05 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/07 11:40:47 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*add_void_token(t_list *tmp, t_struct *root, int flag)
{
	t_token_cmd	*token;
	t_list		*new;
	char		*input;
	int			type;

	if (flag == 5)
		type = d_quot_str;
	else
		type = s_quot_str;
	input = ft_strdup("");
	tmp = tmp->next;
	token = create_new_token_cmd(input, type, tmp);
	new = ft_lstnew(token);
	ft_lstadd_back(&root->list_cmd, new);
	free(input);
	return (tmp->next);
}
