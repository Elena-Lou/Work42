/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:20:38 by elouisia          #+#    #+#             */
/*   Updated: 2022/06/26 16:30:57 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home_val(t_list *env)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(((t_token_env *)tmp->content)->name, "HOME"))
			return (((t_token_env *)tmp->content)->value);
		tmp = tmp->next;
	}
	return (0);
}

char	**get_pwd_val(t_list *env)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(((t_token_env *)tmp->content)->name, "PWD"))
			return (&((t_token_env *)tmp->content)->value);
		tmp = tmp->next;
	}
	return (0);
}

char	**get_oldpwd_val(t_list *env)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(((t_token_env *)tmp->content)->name, "OLDPWD"))
			return (&((t_token_env *)tmp->content)->value);
		tmp = tmp->next;
	}
	return (0);
}

int	cd_check_args(char **tab_cmd)
{
	int	i;

	i = 0;
	while (tab_cmd[i])
		i++;
	if (i > 2)
	{
		ft_printf("minishell: cd: too many arguments\n");
		g_error = 1;
		return (1);
	}
	return (0);
}

void	cd_init_struct(t_env_val *env_val, t_list *env)
{
	env_val->home = get_home_val(env);
	env_val->pwd = get_pwd_val(env);
	env_val->oldpwd = get_oldpwd_val(env);
}
