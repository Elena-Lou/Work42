/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:40:29 by elouisia          #+#    #+#             */
/*   Updated: 2022/06/24 15:15:44 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_check_first_char(char *line)
{
	if (!ft_isalpha(line[0]) && line[0] != '-' && line[0] != '_')
	{
		ft_printf("minishell: unset: '%s': not a valid identifier\n", line);
		g_error = 1;
		return (1);
	}
	return (0);
}

int	check_unset_identifier(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[0] == '-' && line[1] != '\0')
		{
			ft_printf("minishell: unset: -%c: invalid option\n", line[1]);
			g_error = 2;
			return (1);
		}
		else if (!ft_isalnum(line[i]) && line[i] != '_' && line[i] != '$')
		{
			ft_printf("minishell: unset: '%s': not a valid identifier\n", line);
			g_error = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

int	unset_check(char *line)
{
	if (!unset_check_first_char(line) && !check_unset_identifier(line))
		return (0);
	else
		return (1);
}
