/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 12:17:40 by elouisia          #+#    #+#             */
/*   Updated: 2022/02/11 16:18:00 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>

int		ft_pipex(char **av, char **env, int infile, int outfile);
char	*get_path(char **env);
void	check_path(char *cmd, char *path, char **env);
void	free_tab(char **tab);

#endif