/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_simple_cmd_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdubilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:57:14 by jdubilla          #+#    #+#             */
/*   Updated: 2022/05/31 10:59:41 by jdubilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*return_value(char *value, t_list *tmp)
{
	while (is_word(tmp) && tmp->next && is_word(tmp->next)
		&& ((t_token_cmd *)tmp->content)->space_after == 0)
	{
		value = ft_strjoin_ter(value,
				((t_token_cmd *)tmp->next->content)->value);
		tmp = tmp->next;
	}
	return (value);
}

t_list	*return_tmp(t_list *tmp)
{
	while (is_word(tmp) && tmp->next && is_word(tmp->next)
		&& ((t_token_cmd *)tmp->content)->space_after == 0)
		tmp = tmp->next;
	return (tmp);
}
