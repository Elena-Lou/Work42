/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdubilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 20:04:13 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/22 20:51:30 by jdubilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name(char *line, t_struct *root)
{
	int		i;
	char	*res;

	i = 0;
	while (line[i] != '=')
		i++;
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
	{
		free_double_array(root->env);
		ft_printf("minishell: malloc: allocation failed\n");
		exit(1);
	}
	i = 0;
	while (line[i] != '=')
	{
		res[i] = line[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*get_value(char *line)
{
	int		start;
	int		i;
	char	*res;

	start = 0;
	i = 0;
	while (line[start] != '=')
		start++;
	start++;
	while (line[start + i])
		i++;
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
	{
		ft_printf("minishell: malloc: allocation failed\n");
		exit(1);
	}
	i = 0;
	while (line[start + i])
	{
		res[i] = line[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

t_token_env	*create_new_token_env(char *name, char *value)
{
	t_token_env	*token;

	token = malloc(sizeof(t_token_env));
	if (!token)
	{
		free(name);
		free(value);
		ft_printf("minishell: malloc: allocation failed\n");
		exit(1);
	}
	token->name = name;
	token->value = value;
	return (token);
}

static void	creat_lst_env(t_struct *root, char *line)
{
	char		*name;
	char		*value;
	t_list		*new;
	t_token_env	*token;

	name = get_name(line, root);
	value = get_value(line);
	token = create_new_token_env(name, value);
	new = ft_lstnew(token);
	ft_lstadd_back(&root->list_env, new);
}

void	lst_env(t_struct *root)
{
	int	i;

	i = 0;
	while (root->env[i])
	{
		creat_lst_env(root, root->env[i]);
		i++;
	}
}
