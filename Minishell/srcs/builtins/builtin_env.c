/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:49:07 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/26 17:51:55 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_name_value(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc(sizeof(*res) * (len + 3));
	if (!res)
		return (NULL);
	while (s1[i])
		res[j++] = s1[i++];
	i = 0;
	res[j++] = '=';
	while (s2[i])
		res[j++] = s2[i++];
	res[j++] = '\n';
	res[j] = '\0';
	return (res);
}

void	builtin_env(t_list *env)
{
	t_list	*tmp;
	char	*str;

	g_error = 0;
	tmp = env;
	while (tmp)
	{
		str = join_name_value(((t_token_env *)tmp->content)->name,
				((t_token_env *)tmp->content)->value);
		if (write(1, str, ft_strlen(str)) == -1)
		{
			ft_printf("minishell: env: write error: %s\n", strerror(errno));
			free(str);
			g_error = 125;
			return ;
		}
		free(str);
		tmp = tmp->next;
	}
}
