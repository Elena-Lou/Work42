/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntaxe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:42:51 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/27 14:54:45 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_double_and_last_operator(t_list *tmp)
{
	char	*value;
	char	*value_bis;

	while (tmp)
	{
		if (is_operator_error_ter(tmp) && tmp->next && is_operator(tmp->next))
		{
			value = ((t_token_cmd *)tmp->next->content)->value;
			if (is_operator_error_bis(tmp->next))
				get_error(value[0], value[1]);
			else if (tmp->next->next && is_operator_error_ter(tmp->next->next)
				&& ((t_token_cmd *)tmp->next->content)->space_after == 0)
			{
				value_bis = ((t_token_cmd *)tmp->next->next->content)->value;
				get_error(value[0], value_bis[0]);
			}
			else
				ft_printf("minishell: syntax error near unexpected token `%c'\n",
					value[0]);
			g_error = 2;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static int	check_false_operator(t_list *tmp)
{
	char	*value;

	while (tmp)
	{
		if (is_operator_error(tmp))
		{
			value = ((t_token_cmd *)tmp->content)->value;
			if (ft_strlen(value) > 3)
			{
				get_error(value[2], value[3]);
				g_error = 2;
				return (1);
			}
			else if (ft_strlen(value) > 2)
			{
				ft_printf("minishell: syntax error near unexpected token `%c'\n",
					value[2]);
				g_error = 2;
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

static int	check_last_operator(t_list *tmp)
{
	while (tmp)
	{
		if (is_operator(tmp) && tmp->next == NULL)
		{
			ft_printf("bash: syntax error near unexpected token `newline'\n");
			g_error = 2;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static int	check_first_operator(t_list *tmp)
{
	if (((t_token_cmd *)tmp->content)->type == pipe_c)
	{
		if (ft_strlen(((t_token_cmd *)tmp->content)->value) > 1)
			ft_printf("minishell: syntax error near unexpected token `||'\n");
		else
			ft_printf("minishell: syntax error near unexpected token `|'\n");
		g_error = 2;
		return (1);
	}
	return (0);
}

int	check_syntaxe(t_struct *root)
{
	t_list	*tmp;

	tmp = root->list_cmd_bis;
	if (check_first_operator(tmp))
		return (1);
	if (check_false_operator(tmp))
		return (1);
	else if (check_double_and_last_operator(tmp))
		return (1);
	else if (check_last_operator(tmp))
		return (1);
	return (0);
}
