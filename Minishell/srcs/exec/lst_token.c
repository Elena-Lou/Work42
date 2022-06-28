/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdubilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:16:27 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/22 20:42:10 by jdubilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Suppression du type '\' car on ne doit pas l'interpreter, on le considere
	donc comme un caractere comme un autre.

	Suppression egalement du type '$' car il sera gere plus tard dans le parsing

	Suppression du type ';', on le considere egalement comme un char comme un autre
	sans l'interpreter */

	// norme

static int	get_type_token(char c)
{
	if (c == '<')
		return (2);
	else if (c == '>')
		return (3);
	else if (c == '|')
		return (4);
	else if (c == '"')
		return (5);
	else if (c == '\'')
		return (6);
	else if (c == ' ')
		return (9);
	else
		return (1);
}

static t_token	*create_new_token(char l, int flags, t_struct *root)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		free(root->line);
		ft_lstclear(&root->list_token, &free_lst_token);
		free_double_array(root->env);
		rl_clear_history();
		ft_printf("minishell: malloc: allocation failed\n");
		exit(1);
	}
	token->c = l;
	token->flag = flags;
	return (token);
}

static void	creat_lst_token(char c, t_struct *root)
{
	int		type;
	t_list	*new;
	t_token	*token;

	type = get_type_token(c);
	token = create_new_token(c, type, root);
	new = ft_lstnew(token);
	ft_lstadd_back(&root->list_token, new);
}

void	lst_token(char *line, t_struct *root)
{
	int	i;

	i = 0;
	while (line[i])
	{
		creat_lst_token(line[i], root);
		i++;
	}
}
