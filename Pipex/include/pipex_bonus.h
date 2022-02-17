/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:18:12 by elouisia          #+#    #+#             */
/*   Updated: 2022/02/17 17:02:23 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>

typedef struct s_pipexbonus
{
	char	*path;
	char	**av;
	char	**env;
	char	**tab_path;
}	t_databonus;

/*
**	fonctions pipex
*/

int		ft_pipex(int ac, int *file, t_databonus *data);
char	*get_path(char **env);
void	execute_cmd(t_databonus *data, char *cmd);
void	free_tab(char **tab);
int		check_files(int *file, char *av);
void	set_data(char **av, char **env, t_databonus *data, int file[2]);

/*
**	fonctions annexes
*/

char	*ft_strnstr(const char *big, const char *little, size_t len);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char const *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
size_t	ft_strlen(const char *s);

#endif