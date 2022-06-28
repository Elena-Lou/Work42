/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdubilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:49:04 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/21 00:40:29 by jdubilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_pwd(t_list *env)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(((t_token_env *)tmp->content)->name, "PWD"))
		{
			printf("%s\n", ((t_token_env *)tmp->content)->value);
			return ;
		}
		tmp = tmp->next;
	}
}

void	builtin_pwd(char **tab_cmd, t_list *env)
{
	int	i;

	i = 0;
	while (tab_cmd[i])
	{
		if (tab_cmd[i][0] == '-')
		{
			if (tab_cmd[i][1] != '\0')
			{
				ft_printf("minishell: pwd: -%c: invalid option\n",
					tab_cmd[i][1]);
				g_error = 2;
				return ;
			}
		}
		i++;
	}
	print_pwd(env);
	g_error = 0;
}
