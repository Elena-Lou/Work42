/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:14:33 by elouisia          #+#    #+#             */
/*   Updated: 2022/06/26 16:31:04 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_pwd(t_env_val *env_val)
{
	char	*save;

	save = ft_strdup(*env_val->pwd);
	if (!save)
		return ;
	free(*env_val->pwd);
	*env_val->pwd = ft_strdup(getcwd(NULL, 0));
	if (!*env_val->pwd)
		return ;
	free(*env_val->oldpwd);
	*env_val->oldpwd = ft_strdup(save);
	if (!*env_val->oldpwd)
		return ;
	free(save);
}

static void	reverse_pwd_oldpwd(t_env_val *env_val)
{
	char	*save;

	save = ft_strdup(*env_val->pwd);
	if (!save)
		return ;
	free(*env_val->pwd);
	*env_val->pwd = ft_strdup(*env_val->oldpwd);
	if (!*env_val->pwd)
		return ;
	free(*env_val->oldpwd);
	*env_val->oldpwd = ft_strdup(save);
	if (!*env_val->oldpwd)
		return ;
	free(save);
	printf("%s\n", *env_val->pwd);
	if (chdir(*env_val->pwd) == -1)
	{
		ft_printf("minishell: cd: %s: %s\n", *env_val->pwd, strerror(errno));
		g_error = 1;
		return ;
	}	
}

static void	cd_return_home(char *path, t_env_val *env_val)
{	
	if (chdir(env_val->home) == -1)
	{
		ft_printf("minishell: cd: %s: %s\n", path, strerror(errno));
		g_error = 1;
		return ;
	}
	set_pwd(env_val);
}

static void	cd_follow_cmd(char *path, t_env_val *env_val)
{
	if (chdir(path) == -1)
	{
		ft_printf("minishell: cd: %s: %s\n", path, strerror(errno));
		g_error = 1;
		return ;
	}
	set_pwd(env_val);
}

void	builtin_cd(char **tab_cmd, t_list *env)
{
	t_env_val	env_val;

	g_error = 0;
	if (cd_check_args(tab_cmd))
		return ;
	cd_init_struct(&env_val, env);
	if (tab_cmd[1] == NULL || (tab_cmd[1][0] == '-' && tab_cmd[1][1] == '-'))
		cd_return_home(tab_cmd[1], &env_val);
	else if (tab_cmd[1][0] == '-' && tab_cmd[1][1] == '\0')
		reverse_pwd_oldpwd(&env_val);
	else
		cd_follow_cmd(tab_cmd[1], &env_val);
}
