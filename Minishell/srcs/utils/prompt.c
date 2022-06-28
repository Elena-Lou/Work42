/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:55:15 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/27 13:27:25 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_prompt(void)
{
	char	*line;

	if (g_error == 0)
		line = readline("✅\033[34;01m Minishell 👉 \033[00m");
	else
		line = readline("❌\033[34;01m Minishell 👉 \033[00m");
	return (line);
}

void	signal_ctrl_c(int nb)
{
	(void)nb;
	g_error = 130;
	rl_on_new_line();
	printf ("\n");
	rl_replace_line("", 0);
	rl_redisplay();
}
