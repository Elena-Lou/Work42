/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 10:20:22 by elouisia          #+#    #+#             */
/*   Updated: 2022/08/08 14:02:02 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <errno.h>
# include <sys/time.h>
# include <string.h>

# ifndef SUCCESS
#  define SUCCESS 0
# endif 

# ifndef FAILURE
#  define FAILURE 1
# endif

# ifndef ERROR
#  define ERROR 2
# endif

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	f_mutex;
}	t_fork;

typedef struct s_philo
{
	pthread_mutex_t	c_mutex;
	int				philo_id;
	t_fork			*l_fork;
	t_fork			*r_fork;
	int				nb_philo;
	unsigned int	cigue_ti;
	int				banquet_ti;
	int				dream_ti;
	int				m_count;
	int				m_nb;
	unsigned int	launch_time;
	unsigned int	start;
	unsigned int	last_banquet;
	struct s_root	*root;
	t_fork			*fork;
}	t_philo;

typedef struct s_root
{
	pthread_mutex_t	root_mutex;
	unsigned int	launch_time;
	int				schroedinger;
	int				printed;
	pthread_t		*th;
	int				nb_philo;
	unsigned int	cigue_ti;
	int				banquet_ti;
	int				dream_ti;
	int				m_nb;
	t_philo			*camus;
	t_fork			*fork;
}	t_root;

/*
**	MAIN.C
*/

int				delayed_launch(t_philo *camus);
void			mutex_destroyer(t_root *root);

/*
**	STRUCT_INIT.C
*/

int				ft_init(int ac, char **av, t_root *root);
void			philo_init(t_philo *camus, int i, t_root *root);
int				struct_init(int ac, char **av, t_root *root);
void			fork_init(t_root *root);

/*
**	UTILS.C
*/

int				ft_atol(const char *str);
int				ft_isdigit(int c);
int				ft_strlen(char *str);
void			ft_putnbr(int i);

/*
**	ARG_CHECKS.C
*/

int				check_numbers(t_root *root, int ac);
int				arg_checks(int ac, char **av);

/*
**	TIME_MANAGEMENT.C
*/

unsigned int	get_time(void);
unsigned int	timestamp(t_philo *camus);
int				custom_usleep_death(t_philo *camus, unsigned int t);
void			custom_usleep(unsigned int t);

/*
**	PRINTS.C
*/

void			print_msg(t_philo *camus, char *msg);

/*
**	ROUTINE.C
*/

void			*ft_routine(void *void_camus);
int				ft_daily_routine(t_philo *camus);
int				ft_think(t_philo *camus);
int				ft_dream(t_philo *camus);

/*
**	CAKEORDEATH.c
*/

int				cake_or_death(t_philo *camus, char *msg);

/*
**	HADES.C
*/

void			are_you_dead(t_philo *camus, int i);

/*
**	BANQUET.C
*/

int				grab_forks(t_philo *camus);
int				drop_forks(t_philo *camus);
int				ft_banquet(t_philo *camus);

#endif