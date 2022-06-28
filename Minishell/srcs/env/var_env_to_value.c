/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env_to_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdubilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 10:50:42 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/23 22:14:34 by jdubilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_and_add_var(char *res, int *i, t_list *tmp, t_struct *root)
{
	int		start;
	int		len;
	char	*cpy_var;
	char	*value_var;
	char	*str;

	start = *i;
	len = 0;
	str = ((t_token_cmd *)tmp->content)->value;
	while (str[*i] && ft_isalnum(str[*i]))
	{
		len++;
		*i += 1;
	}
	if (len > 0)
	{
		cpy_var = cpy_name_var(start, len, str, root);
		value_var = check_var_exist(root, cpy_var);
		if (value_var && ((t_token_cmd *)tmp->content)->type == literal)
			res = ft_strjoin_env_literal(res, value_var);
		else if (value_var)
			res = ft_strjoin_ter(res, value_var);
		*i -= 1;
	}
	return (res);
}

static char	*check_dollar_bis(t_list *tmp, int *i, char *res, t_struct *root)
{
	char	*error;
	char	*str;

	*i += 1;
	str = ((t_token_cmd *)tmp->content)->value;
	if (str[*i] == '?')
	{
		error = ft_itoa(g_error);
		res = ft_strjoin_ter(res, error);
		free(error);
	}
	if (str[*i] == '=')
		res = ft_strjoin_ter(res, "$=");
	else if (ft_isdigit(str[*i]))
		return (res);
	else if (str[*i] == ' ')
		res = add_word(str, i, res);
	else
		res = check_and_add_var(res, i, tmp, root);
	return (res);
}

static char	*var_env_literal_bis(char *res, int i, t_list *tmp, t_struct *root)
{
	char	*str;

	str = ((t_token_cmd *)tmp->content)->value;
	while (str[++i])
	{
		while (str[i] != '$')
		{
			res = ft_strjoin(res, str[i++]);
			if (str[i] == '\0')
				return (res);
		}
		if (str[i] == '$')
		{
			if (str[i] == '$' && (str[i + 1] == '\0'))
				res = check_void_dollar(tmp, res, &i);
			else if (str[i] == '$' && (ft_isalnum(str[i + 1])
					|| str[i + 1] == '?'))
				res = check_dollar_bis(tmp, &i, res, root);
			else
				res = ft_strjoin(res, str[i]);
		}
	}
	return (res);
}

static char	*check_var_env_literal(t_struct *root, char *str, t_list *tmp)
{
	int		i;
	char	*res;

	i = -1;
	res = NULL;
	if (ft_strlen(str) == 1 && str[0] == '~')
	{
		res = check_tilde(tmp, res);
		return (res);
	}
	else if (ft_strlen(str) > 1 && str[0] == '~' && str[1] == '/')
	{
		res = ft_strjoin_ter(res, "/mnt/nfs/homes/jdubilla/");
		i = 2;
		while (str[i] != '$')
		{
			res = ft_strjoin(res, str[i++]);
			if (str[i] == '\0')
				return (res);
		}
	}
	res = var_env_literal_bis(res, i, tmp, root);
	return (res);
}

void	var_env_to_value(t_struct *root)
{
	char		*new_value;
	t_list		*tmp;

	tmp = root->list_cmd;
	while (tmp)
	{
		if (tmp->prev && ((t_token_cmd *)tmp->prev->content)->type == d_chvr_g)
			add_element(((t_token_cmd *)tmp->content)->value,
				((t_token_cmd *)tmp->content)->type, root, tmp);
		else if (((t_token_cmd *)tmp->content)->type == d_quot_str
			|| ((t_token_cmd *)tmp->content)->type == literal)
		{
			new_value = check_var_env_literal(root,
					((t_token_cmd *)tmp->content)->value, tmp);
			if (new_value)
				add_new_value_to_lst(tmp, new_value, root);
			else if (!new_value
				&& ((t_token_cmd *)tmp->content)->type == d_quot_str)
				add_void_new_value_to_lst(tmp, new_value, root);
		}
		else
			add_element(((t_token_cmd *)tmp->content)->value,
				((t_token_cmd *)tmp->content)->type, root, tmp);
		tmp = tmp->next;
	}
}
