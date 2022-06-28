/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdubilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 17:50:05 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/22 03:29:21 by jdubilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lst_token(void *content)
{
	t_token	*token;

	token = content;
	printf("char : %c flag = %d\n", token->c, token->flag);
}

void	print_lst_cmd(void *content)
{
	t_token_cmd	*token;

	token = content;
	printf("value : %s. type : %d. space = %d\n", token->value, token->type,
		token->space_after);
}

void	print_lst_token_env(void *content)
{
	t_token_env	*token;

	token = content;
	printf("name : %s\nvalue : %s\n", token->name, token->value);
}

void	print_lst_simple_cmd(void *content)
{
	t_token_cmd	*token;

	token = content;
	printf("value : %s. type : %d.\n", token->value, token->type);
}

void	print_lst_pipe(void *content)
{
	int				i;
	t_token_pipe	*token;

	token = content;
	i = 0;
	printf("tab_cmd:\n");
	if (token->tab_cmd)
	{
		while (token->tab_cmd[i])
		{
			printf("tab_cmd[%d] = %s\n", i, token->tab_cmd[i]);
			i++;
		}
	}
	printf("fd_infile: %d fd_outfile: %d ", token->fd_infile,
		token->fd_outfile);
	printf("exec: %d\n\n", token->exec);
}
