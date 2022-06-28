/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdubilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:57:03 by elouisia          #+#    #+#             */
/*   Updated: 2022/06/26 19:05:29 by jdubilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_or_replace_var(t_list *env, char *name, char *value)
{
	t_list		*tmp;
	t_list		*new;
	t_token_env	*token;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(((t_token_env *)tmp->content)->name, name))
		{
			free(((t_token_env *)tmp->content)->value);
			((t_token_env *)tmp->content)->value = ft_strdup(value);
			if (!((t_token_env *)tmp->content)->value)
				return ;
			free(name);
			free(value);
			return ;
		}
		tmp = tmp->next;
	}
	token = create_new_token_env(name, value);
	new = ft_lstnew(token);
	ft_lstadd_back(&env, new);
	return ;
}

int	check_join(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '+' && line[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	join_existing_var(t_list *env, char *name, char *value)
{
	t_list	*tmp;
	char	*prv_val;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(((t_token_env *)tmp->content)->name, name))
		{
			prv_val = ft_strdup(((t_token_env *)tmp->content)->value);
			free(((t_token_env *)tmp->content)->value);
			((t_token_env *)tmp->content)->value
				= ft_strjoin_ter(prv_val, value);
			if (!((t_token_env *)tmp->content)->value)
				return ;
		}
		tmp = tmp->next;
	}
	return ;
}

void	builtin_export(char **tab_cmd, t_list *env)
{
	char	*name;
	char	*value;
	int		i;

	i = 0;
	g_error = 0;
	if (!tab_cmd[1])
	{
		ft_printf("minishell: export: incorrect number of arguments\n");
		return ;
	}
	while (tab_cmd[++i])
	{
		if (!export_check(tab_cmd[i]))
		{
			name = export_get_name(tab_cmd[i]);
			value = get_value(tab_cmd[i]);
			if (!check_join(tab_cmd[i]))
				add_or_replace_var(env, name, value);
			else
				join_existing_var(env, name, value);
		}
	}
}
