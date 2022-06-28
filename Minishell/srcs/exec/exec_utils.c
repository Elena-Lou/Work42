/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdubilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 18:40:26 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/22 20:56:20 by jdubilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nbr_word_cmd(t_struct *root)
{
	t_list	*tmp;
	int		i;

	tmp = root->list_simpl_cmd;
	i = 0;
	while (tmp)
	{
		if (is_word(tmp))
			i++;
		tmp = tmp->next;
	}
	if (i == 0)
		g_error = 0;
	return (i);
}

char	**word_to_tab(int nbr_word, t_list *tmp, t_struct *root)
{
	char	**tab_cmd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tab_cmd = malloc(sizeof(char *) * (nbr_word + 1));
	check_malloc_word_to_tab(root, tab_cmd);
	while (i < nbr_word && tmp)
	{
		if (!ft_strcmp(((t_token_cmd *)tmp->content)->value, "env")
			&& i + 1 < nbr_word)
		{
			i++;
			j++;
		}
		else if (is_word(tmp))
		{
			tab_cmd[i - j] = ft_strdup(((t_token_cmd *)tmp->content)->value);
			i++;
		}
		tmp = tmp->next;
	}
	tab_cmd[i] = NULL;
	return (tab_cmd);
}

void	free_double_array(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_tab_exec_cmd(char *test_path, char **tab_cmd, char **path_splt)
{
	free(test_path);
	free_double_array(tab_cmd);
	free_double_array(path_splt);
}

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "/usr/bin/echo")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "/usr/bin/env")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "/usr/bin/pwd")
		|| !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}
