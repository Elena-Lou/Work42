/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:41:50 by jdubilla          #+#    #+#             */
/*   Updated: 2022/06/27 13:27:09 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "ft_printf.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>

extern int	g_error;

enum e_type
{
	literal,
	pipe_c,
	chvr_d,
	chvr_g,
	d_chvr_d,
	d_chvr_g,
	d_quot_str,
	s_quot_str
};

typedef struct s_env_values
{
	char	*home;
	char	**pwd;
	char	**oldpwd;
}	t_env_val;

typedef struct s_token
{
	char	c;
	int		flag;
}					t_token;

typedef struct s_token_cmd
{
	char	*value;
	int		type;
	int		space_after;
}					t_token_cmd;

typedef struct s_token_pipe
{
	char	**tab_cmd;
	int		fd_infile;
	int		fd_outfile;
	int		exec;
	int		nbr_here_doc;
	int		err;
}					t_token_pipe;

typedef struct s_token_env
{
	char	*name;
	char	*value;
}					t_token_env;

typedef struct s_simpl_cmd
{
	int	filein;
	int	fileout;
	int	cpy_stdin;
	int	cpy_stdout;
	int	fd_stdin;
	int	fd_stdout;
	int	err_env;
	int	is_heredoc;
	int	nbr_here_doc;
}		t_simpl_cmd;

typedef struct s_struct
{
	int			ret;
	char		*line;
	char		**env;
	t_list		*list_token;
	t_list		*list_cmd;
	t_list		*list_env;
	t_list		*list_pipe;
	t_list		*list_cmd_bis;
	t_list		*list_simpl_cmd;
	t_simpl_cmd	*info_simpl_cmd;
}		t_struct;

/*
** 	LST_UTILS.C
*/

void		print_lst_cmd(void *content);
void		print_lst_pipe(void *content);
void		print_lst_token(void *content);
void		print_lst_token_env(void *content);
void		print_lst_simple_cmd(void *content);

/*
** 	LST_UTILS_BIS.C
*/

void		free_lst_cmd(void *content);
void		free_lst_pipe(void *content);
void		free_lst_token(void *content);
void		free_lst_token_env(void *content);
void		add_element(char *new_value, int type, t_struct *root, t_list *tmp);

/*
**	PROMPT.C
*/

char		*create_prompt(void);
void		signal_ctrl_c(int nb);

/*
**	BUILTINS_FUNCTIONS
*/

void		builtin_pwd(char **tab_cmd, t_list *env);
void		builtin_env(t_list *env);
int			builtin_exit(t_struct *root, char **tab_cmd, int pipe);
void		builtin_echo(char **tab_cmd);
void		builtin_cd(char **tab_cmd, t_list *env);

/*
** BUILTIN_EXIT_UTILS.C
*/

int			check_last_ret_pipe(t_list *tmp);
void		get_message_builtin_exit(int pipe, int message, char *str);
int			check_error_exit_bis(int pipe, t_struct *root, char **tab_cmd);
void		free_all_builtin_exit(t_struct *root, char **tab_cmd, int pipe);
int			check_error_exit(int ret, int pipe, t_struct *root, char **tab_cmd);

/*
** BUILTIN_CD_UTILS.C
*/

char		**get_oldpwd_val(t_list *env);
char		**get_pwd_val(t_list *env);
char		*get_home_val(t_list *env);
int			cd_check_args(char **tab_cmd);
void		cd_init_struct(t_env_val *env_val, t_list *env);

/*
** BUILTIN_EXPORT.C
*/

void		add_or_replace_var(t_list *env, char *name, char *value);
int			check_join(char *line);
void		join_existing_var(t_list *env, char *name, char *value);
void		builtin_export(char **tab_cmd, t_list *env);

/*
** BUILTIN_EXPORT_UTILS.C
*/

int			check_first_char(char *line);
int			check_empty_value(char *line);
int			check_export_option(char *line);
char		*export_get_name(char *line);
int			export_check(char *line);

/*
** BUILTIN_UNSET.C
*/

void		free_element_unset(t_list *tmp);
void		builtin_unset(char **tab_cmd, t_list **env);

/*
** BUILTIN_UNSET_UTILS.C
*/

int			unset_check_first_char(char *line);
int			check_unset_identifier(char *line);
int			unset_check(char *line);

/*
**	CHECK_ERROR.C
*/

int			check_return_fd(int fd);
int			check_void_line(char *line);
int			check_quotes_error(char *line);
void		check_malloc_word_to_tab(t_struct *root, char **tab_cmd);

/*
**	CHECK_INFILE_OUTFILE.C
*/

int			check_infile_outfile(t_struct *root);

/*
**	CHECK_INFILE_OUTFILE_UTILS.C
*/

void		open_fd_here_doc(t_struct *root);
void		message_check_infile(char *value);
void		open_outfile(int type, char *value, t_struct *root);
void		check_infile_bis(t_struct *root, int i, int fd, int pos_here_doc);

/*
**	CHECK_SYNTAXE.C
*/

int			check_syntaxe(t_struct *root);

/*
**	CHECK_SYNTAXE_UTILS.C
*/

void		get_error(char c, char d);
int			check_pipe(t_struct *root);
int			is_operator_error(t_list *tmp);
int			is_operator_error_bis(t_list *tmp);
int			is_operator_error_ter(t_list *tmp);

/*
**	EXEC.C
*/

void		exec_simple_cmd(t_struct *root);
void		execute_cmd(t_struct *root, char **tab_cmd);

/*
**	EXEC_UTILS.C
*/

int			is_builtin(char *cmd);
void		free_double_array(char **tab);
int			nbr_word_cmd(t_struct *root);
char		**word_to_tab(int nbr_word, t_list *tmp, t_struct *root);
void		free_tab_exec_cmd(char *test_path, char **tab_cmd,
				char **path_splt);

/*
**	EXEC_UTILS_BIS.C
*/

void		execute_builtin(t_struct *root, char **tab_cmd, int pipe);
void		path_error(char **tab_cmd, char **path_split, t_struct *root);
void		redirect_and_exec_builtin(t_struct *root, char **tab_cmd, int pipe);
void		redirect_and_exec(t_struct *root, char *test_path, char **tab_cmd);

/*
**	EXEC_UTILS_TER.C
*/

int			check_dir(char *arg);
void		close_fds(t_struct *root);
void		clear_redir(t_struct *root);
char		*check_envp(t_list *tmp, char **tab_cmd);
void		execute_cmd_with_path(char **tab_cmd, t_struct *root);

/*
**	EXEC_UTILS_QUA.C
*/

void		get_exit_status(t_struct *root, pid_t pid);

/*
**	EXEC_PIPE.C
*/

void		exec_pipe(t_struct *root);

/*
**	EXEC_PIPE_UTILS.C
*/

void		fork_all_cmd_bis(t_struct *root, t_list *lst_pipe,
				pid_t *pid, int i);

/*
**	EXEC_PIPE_UTILS_BIS.C
*/

void		close_all_fds(t_list *lst_pipe);
void		free_all_pipe(t_struct *root, int *pid);
void		init_pipe(t_list *lst_pipe, int i, int **tab_fd);
void		path_error_pipe(char **tab_cmd, t_struct *root, int *pid);
void		test_path_exec(char **path_split, t_struct *root,
				t_list *tmp, int *pid);

/*
**	EXEC_PIPE_UTILS_TER.C
*/

void		return_error_pipe(int nb);
void		free_tab_fd(int **tab_fd);
void		free_tab_exec_cmd_pipe(char *test_path, char **path_splt);

/*
**	GET_TYPE.C
*/

int			is_word(t_list *tmp);
int			get_type(char *input);
int			is_operator(t_list *tmp);
int			is_redirection(t_list *tmp);

/*
**	INIT_STRUCT.C
*/

void		init_struct_pipe(t_token_pipe *infos_pipe, t_list *tmp);
void		clear_struct(t_struct *root, t_simpl_cmd *simpl_cmd);
void		init_struct(t_struct *root, t_simpl_cmd	*simpl_cmd, char **envp);

/*
**	LST_CMD.C
*/

void		join_token(t_struct *root, t_list *tmp);
t_token_cmd	*create_new_token_cmd(char *value, int type, t_list *tmp);

/*
**	LST_CMD_UTILS.C
*/

t_list		*add_void_token(t_list *tmp, t_struct *root, int flag);

/*
**	LST_ENV.C
*/

void		lst_env(t_struct *root);
t_token_env	*create_new_token_env(char *name, char *value);
char		*get_name(char *line, t_struct *root);
char		*get_value(char *line);

/*
**	LST_SIMPLE_CMD.C
*/

void		lst_simple_cmd(t_struct *root);

/*
**	LST_SIMPLE_CMD_UTILS.C
*/

t_list		*return_tmp(t_list *tmp);
char		*return_value(char *value, t_list *tmp);

/*
**	LST_TOKEN.C
*/

void		lst_token(char *line, t_struct *root);

/*
**	LST_PIPE.C
*/

int			lst_pipe(t_struct *root);

/*
**	LST_PIPE_UTILS.C
*/

int			here_doc_pipe(t_list *tmp, t_token_pipe *inf_pipe, int i);
void		check_outfile_pipe(t_list *tmp, t_token_pipe *inf_pipe);
void		check_infile_pipe(t_list *tmp, t_token_pipe *inf_pipe,
				int here_doc);

/*
**	LST_PIPE_UTILS_BIS.C
*/

char		*get_new_name(char *name, int i);
void		check_close_fd_pipe(t_token_pipe *inf_pipe);
int			check_finish_here_doc(char *str, char *limi,
				int fd, t_token_pipe *inf_pip);
int			check_error_here_doc_pipe(char *s, int i, char *lim,
				t_token_pipe *inf_pip);
int			check_fd_lst_pipe(int fd, char *value, t_token_pipe *inf_pipe);

/*
**	LST_PIPE_UTILS_TER.C
*/

int			nbr_word_cmd_pipe(t_list *tmp);
int			check_fd_lst_pipe_bis(int fd, char *value);
int			check_fd_lst_pipe_ter(int fd, t_token_pipe *inf_pipe);
int			open_fd_here_doc_pipe_bis(t_token_pipe *inf_pip,
				char *new_name, int i);
void		open_fd_here_doc_pipe(t_token_pipe *inf_pipe, char *new_name);

/*
**	VAR_ENV_TO_VALUE.C
*/

void		var_env_to_value(t_struct *root);

/*
**	VAR_ENV_TO_VALUE_UTILS.C
*/

char		*cpy_name_var(int start, int len, char *str, t_struct *root);
char		*check_var_exist(t_struct *root, char *cpy_var);
void		add_new_value_to_lst(t_list *tmp, char *new_value, t_struct *root);
void		add_void_new_value_to_lst(t_list *tmp, char *new_value,
				t_struct *root);
t_token_cmd	*create_new_token_cmd_bis(char *value, int type, int space);

/*
**	VAR_ENV_TO_VALUE_UTILS_BIS.C
*/

char		*check_tilde(t_list *tmp, char *res);
char		*add_word(char *str, int *i, char *res);
char		*ft_strjoin_env_literal(char *s1, char *s2);
char		*check_void_dollar(t_list *tmp, char *res, int *i);

/*
**	VAR_ENV_TO_VALUE_UTILS_TER.C
*/

void		add_void_new_value_to_lst(t_list *tmp, char *new_value,
				t_struct *root);

/*
**	HERE_DOC.C
*/

char		*ft_strcpy_bis(char *str);
void		wait_good_line(char *limiter, int fd, int *ret, t_struct *root);

#endif