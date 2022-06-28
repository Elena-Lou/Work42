/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdubilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:39:58 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/27 15:48:26 by jdubilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_error;

void	check_arg(t_struct *root, t_simpl_cmd *simpl_cmd, char **envp, int argc)
{
	g_error = 0;
	if (argc != 1)
	{
		ft_printf("Incorrect number of arguments\n");
		exit(1);
	}
	if (isatty(0) == 0)
	{
		ft_printf("Nope ! \n");
		exit(0);
	}
	init_struct(root, simpl_cmd, envp);
	lst_env(root);
}

void	check_line(char *line, t_struct *root)
{
	if (line == NULL)
	{
		rl_clear_history();
		free(root->line);
		free(line);
		free_double_array(root->env);
		ft_lstclear(&root->list_env, &free_lst_token_env);
		printf("exit\n");
		exit(g_error);
	}
	if (line[0] != '\0')
		add_history(line);
}

void	create_lst(char *line, t_struct *root)
{
	root->line = ft_strjoin(line, ' ');
	lst_token(root->line, root);
	join_token(root, root->list_token);
	ft_lstclear(&root->list_token, &free_lst_token);
	var_env_to_value(root);
	ft_lstclear(&root->list_cmd, &free_lst_cmd);
}

void	go_to_exec(t_struct *root)
{
	lst_simple_cmd(root);
	if (!check_pipe(root))
	{
		if (!check_infile_outfile(root))
			exec_simple_cmd(root);
	}
	else
	{
		if (!lst_pipe(root))
			exec_pipe(root);
		if (root->ret == 1 || check_last_ret_pipe(root->list_pipe) == 1)
			g_error = 1;
		ft_lstclear(&root->list_pipe, &free_lst_pipe);
	}
	ft_lstclear(&root->list_simpl_cmd, &free_lst_cmd);
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	root;
	t_simpl_cmd	simpl_cmd;
	char		*line;

	(void)argv;
	check_arg(&root, &simpl_cmd, envp, argc);
	while (1)
	{
		signal(SIGINT, signal_ctrl_c);
		signal(SIGQUIT, SIG_IGN);
		line = create_prompt();
		check_line(line, &root);
		if (line && !(ft_strlen(line) == 0 && line[0] == '\0')
			&& !check_void_line(line) && !check_quotes_error(line))
		{
			create_lst(line, &root);
			if (ft_lstsize(root.list_cmd_bis) && !check_syntaxe(&root))
				go_to_exec(&root);
			ft_lstclear(&root.list_cmd_bis, &free_lst_cmd);
			clear_struct(&root, &simpl_cmd);
		}
		else
			free(line);
	}
	return (0);
}
