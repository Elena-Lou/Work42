/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdubilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 18:44:02 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/06 19:20:28 by jdubilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(t_list *tmp)
{
	if (((t_token_cmd *)tmp->content)->type == pipe_c
		|| ((t_token_cmd *)tmp->content)->type == chvr_d
		|| ((t_token_cmd *)tmp->content)->type == chvr_g
		|| ((t_token_cmd *)tmp->content)->type == d_chvr_d
		|| ((t_token_cmd *)tmp->content)->type == d_chvr_g)
		return (1);
	return (0);
}

int	is_redirection(t_list *tmp)
{
	if (((t_token_cmd *)tmp->content)->type == chvr_d
		|| ((t_token_cmd *)tmp->content)->type == chvr_g
		|| ((t_token_cmd *)tmp->content)->type == d_chvr_d
		|| ((t_token_cmd *)tmp->content)->type == d_chvr_g)
		return (1);
	return (0);
}

int	is_word(t_list *tmp)
{
	if (((t_token_cmd *)tmp->content)->type == literal
		|| ((t_token_cmd *)tmp->content)->type == d_quot_str
		|| ((t_token_cmd *)tmp->content)->type == s_quot_str)
		return (1);
	return (0);
}

int	get_type(char *input)
{
	if (input[0] == '<')
	{
		if (ft_strlen(input) > 1)
			return (d_chvr_g);
		return (chvr_g);
	}
	if (input[0] == '>')
	{
		if (ft_strlen(input) > 1)
			return (d_chvr_d);
		return (chvr_d);
	}
	else if (input[0] == '|')
		return (pipe_c);
	return (literal);
}
