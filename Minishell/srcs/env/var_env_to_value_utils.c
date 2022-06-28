/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env_to_value_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdubilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:44:29 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/24 21:04:25 by jdubilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_element_bis(char *new_value, int type, t_struct *root, t_list *tmp)
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

void	add_new_value_to_lst(t_list *tmp, char *new_value, t_struct *root)
{
	int		type;
	char	**tab_word;
	int		i;

	i = 0;
	if (((t_token_cmd *)tmp->content)->type == d_quot_str)
	{
		type = ((t_token_cmd *)tmp->content)->type;
		add_element(new_value, type, root, tmp);
	}
	else
	{
		tab_word = ft_split(new_value, ' ');
		while (tab_word[i])
		{
			add_element_bis(tab_word[i], literal, root, tmp);
			i++;
		}
		free_double_array(tab_word);
	}
	free(new_value);
}

t_token_cmd	*create_new_token_cmd_bis(char *value, int type, int space)
{
	t_token_cmd	*token;
	char		*new_value;

	token = malloc(sizeof(t_token_cmd));
	if (!token)
	{
		ft_printf("minishell: malloc: allocation failed\n");
		exit(1);
	}
	new_value = ft_strdup(value);
	token->value = new_value;
	token->type = type;
	token->space_after = space;
	return (token);
}

char	*cpy_name_var(int start, int len, char *str, t_struct *root)
{
	char	*cpy_var;
	int		i;
	int		j;

	cpy_var = malloc(sizeof(char) * (len + 1));
	if (!cpy_var)
	{
		free(root->line);
		free_double_array(root->env);
		ft_lstclear(&root->list_cmd, &free_lst_cmd);
		rl_clear_history();
		ft_printf("minishell: malloc: allocation failed\n");
		exit(1);
	}
	i = 0;
	j = 0;
	while (i < start)
		i++;
	while ((i + j) < (start + len))
	{
		cpy_var[j] = str[i + j];
			j++;
	}
	cpy_var[j] = '\0';
	return (cpy_var);
}

char	*check_var_exist(t_struct *root, char *cpy_var)
{
	t_list	*tmp;
	char	*name_var;

	tmp = root->list_env;
	if (!ft_strcmp(cpy_var, "UID"))
	{
		free(cpy_var);
		return ("101015");
	}
	while (tmp)
	{
		name_var = ((t_token_env *)tmp->content)->name;
		if (ft_strcmp(cpy_var, name_var) == 0)
		{
			free(cpy_var);
			return (((t_token_env *)tmp->content)->value);
		}
		tmp = tmp->next;
	}
	free(cpy_var);
	return (NULL);
}
