/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdubilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 21:36:17 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/26 17:10:42 by jdubilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes_error(char *line)
{
	char	quote;
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i];
			i++;
			while (line[i] != quote)
			{
				if (line[i] == '\0')
				{
					ft_printf("Error, single quote and double quotes");
					ft_printf(" must be closed\n");
					return (1);
				}
				i++;
			}
		}
		i++;
	}
	return (0);
}

int	check_void_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

int	check_return_fd(int fd)
{
	if (fd == -1)
	{
		g_error = 1;
		return (1);
	}
	return (0);
}

void	check_malloc_word_to_tab(t_struct *root, char **tab_cmd)
{
	if (!tab_cmd)
	{
		free(root->line);
		free_double_array(root->env);
		free_double_array(tab_cmd);
		ft_lstclear(&root->list_simpl_cmd, &free_lst_cmd);
		ft_lstclear(&root->list_cmd_bis, &free_lst_cmd);
		ft_lstclear(&root->list_cmd, &free_lst_cmd);
		rl_clear_history();
		ft_printf("minishell: malloc: allocation failed\n");
		exit(1);
	}
}

int	check_last_ret_pipe(t_list *tmp)
{
	while (tmp)
	{
		if (!tmp->next && ((t_token_pipe *)tmp->content)->err == 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
