/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:33:03 by elouisia          #+#    #+#             */
/*   Updated: 2022/06/22 19:02:47 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_element_unset(t_list *tmp)
{
	free(((t_token_env *)tmp->content)->name);
	free(((t_token_env *)tmp->content)->value);
	free(tmp->content);
	free(tmp);
}

void	set_list_ptr(t_list *tmp, t_list **env)
{
	if (tmp->prev == NULL)
	{
		*env = tmp->next;
		tmp->prev = NULL;
		tmp->next = tmp->next->next;
		return ;
	}
	if (tmp->prev != NULL)
		tmp->prev->next = tmp->next;
	if (tmp->next != NULL)
		tmp->next->prev = tmp->prev;
}

void	builtin_unset(char **tab_cmd, t_list **env)
{
	t_list	*tmp;
	int		i;

	i = 0;
	g_error = 0;
	while (tab_cmd[++i])
	{
		if (!unset_check(tab_cmd[i]))
		{
			tmp = *env;
			while (tmp)
			{
				if (!ft_strcmp(((t_token_env *)tmp->content)->name, tab_cmd[i]))
				{
					set_list_ptr(tmp, env);
					free_element_unset(tmp);
					break ;
				}	
				tmp = tmp->next;
			}
		}
	}
}
