/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntaxe_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdubilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:43:43 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/22 02:34:44 by jdubilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator_error(t_list *tmp)
{
	if (((t_token_cmd *)tmp->content)->type == d_chvr_g
		|| ((t_token_cmd *)tmp->content)->type == d_chvr_d
		|| ((t_token_cmd *)tmp->content)->type == pipe_c)
		return (1);
	return (0);
}

int	is_operator_error_bis(t_list *tmp)
{
	if (((t_token_cmd *)tmp->content)->type == d_chvr_g
		|| ((t_token_cmd *)tmp->content)->type == d_chvr_d
		|| ((t_token_cmd *)tmp->content)->type == pipe_c)
		return (1);
	return (0);
}

int	is_operator_error_ter(t_list *tmp)
{
	if (((t_token_cmd *)tmp->content)->type == chvr_d
		|| ((t_token_cmd *)tmp->content)->type == chvr_g
		|| ((t_token_cmd *)tmp->content)->type == d_chvr_d
		|| ((t_token_cmd *)tmp->content)->type == d_chvr_g)
		return (1);
	return (0);
}

int	check_pipe(t_struct *root)
{
	t_list		*tmp;

	tmp = root->list_simpl_cmd;
	while (tmp)
	{
		if (((t_token_cmd *)tmp->content)->type == pipe_c)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	get_error(char c, char d)
{
	ft_printf("minishell: syntax error near unexpected token `%c%c'\n", c, d);
}
