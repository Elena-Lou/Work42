/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env_to_value_utils_bis.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdubilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:46:21 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/22 20:39:05 by jdubilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_word(char *str, int *i, char *res)
{
	*i -= 1;
	while (str[*i])
	{
		res = ft_strjoin(res, str[*i]);
		*i += 1;
		if (str[*i] == '$')
		{
			*i -= 1;
			return (res);
		}
	}
	return (res);
}

char	*check_tilde(t_list *tmp, char *res)
{
	if (((t_token_cmd *)tmp->content)->type != literal)
	{
		res = ft_strjoin(res, '~');
		return (res);
	}
	if (((t_token_cmd *)tmp->content)->space_after == 1)
	{
		if ((tmp->prev && ((t_token_cmd *)tmp->prev->content)->space_after == 1)
			|| !tmp->prev)
		{
			res = ft_strjoin_ter(res, "/mnt/nfs/homes/jdubilla");
			return (res);
		}
	}
	res = ft_strjoin(res, '~');
	return (res);
}

char	*ft_strjoin_env_literal_bis(int j, char *s2, char *res)
{
	int	i;

	i = 0;
	while (s2[i] == ' ')
		i++;
	while (s2[i])
	{
		while (s2[i] && s2[i] != ' ')
			res[j++] = s2[i++];
		while (s2[i] == ' ')
			i++;
		if (s2[i] != '\0')
			res[j++] = ' ';
	}
	res[j] = '\0';
	return (res);
}

char	*ft_strjoin_env_literal(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len;
	char	*res;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc(sizeof(*res) * (len + 1));
	if (!res)
	{
		free(s1);
		rl_clear_history();
		ft_printf("minishell: malloc: allocation failed\n");
		exit(1);
	}
	if (s1)
	{
		while (s1[i])
			res[j++] = s1[i++];
	}
	res = ft_strjoin_env_literal_bis(j, s2, res);
	if (s1)
		free(s1);
	return (res);
}

char	*check_void_dollar(t_list *tmp, char *res, int *i)
{
	*i += 1;
	if (!tmp->next)
		res = ft_strjoin(res, '$');
	else if (((t_token_cmd *)tmp->content)->type == d_quot_str)
		res = ft_strjoin(res, '$');
	else if (((t_token_cmd *)tmp->next->content)->value[0] == '\0')
	{
		if (((t_token_cmd *)tmp->content)->type == literal
			&& ((t_token_cmd *)tmp->content)->space_after == 0)
			res = NULL;
		else
			res = ft_strjoin(res, '$');
	}
	else if (((t_token_cmd *)tmp->content)->type == literal
		&& ((t_token_cmd *)tmp->content)->value[1] == '\0'
		&& ((t_token_cmd *)tmp->content)->space_after == 1)
		res = ft_strjoin(res, '$');
	else if (ft_isalnum(((t_token_cmd *)tmp->next->content)->value[0]))
		res = NULL;
	else
		res = ft_strjoin(res, '$');
	*i -= 1;
	return (res);
}
