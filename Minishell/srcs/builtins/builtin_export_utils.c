/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:54:17 by elouisia          #+#    #+#             */
/*   Updated: 2022/06/27 11:34:15 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_first_char(char *line)
{
	if (!ft_isalpha(line[0]) && line[0] != '-' && line[0] != '_')
	{
		ft_printf("minishell: export: '%s': not a valid identifier\n", line);
		g_error = 1;
		return (1);
	}
	return (0);
}

int	export_check(char *line)
{
	if (!check_first_char(line)
		&& !check_export_option(line)
		&& !check_empty_value(line))
		return (0);
	else
		return (1);
}

char	*export_get_name(char *line)
{
	int		i;
	char	*res;

	i = 0;
	while (line[i] != '=' && line[i] != '+')
	{
		if (line[i] == '+' && line[i + 1] == '=')
			break ;
		i++;
	}
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (0);
	i = 0;
	while (line[i] != '=' && line[i] != '+')
	{
		if (line[i] == '+' && line[i + 1] == '=')
			break ;
		res[i] = line[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

int	check_export_option(char *line)
{
	if (line[0] == '-' && line[1] != '\0')
	{
		ft_printf("minishell: export: -%c: invalid option\n", line[1]);
		g_error = 2;
		return (1);
	}
	return (0);
}

int	check_empty_value(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if ((!ft_isalnum(line[i]) && line[i] != '='
				&& line[i] != '_' && line[i] != '+')
			|| (line[i] == '+' && line[i + 1] != '='))
		{
			ft_printf("minishell: export: '%s': not a valid identifier\n", line);
			g_error = 1;
			return (1);
		}
		else if (line[i] == '=')
			return (0);
		i++;
	}
	return (1);
}
