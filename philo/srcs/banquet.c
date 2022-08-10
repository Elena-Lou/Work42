/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banquet.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 17:36:31 by elouisia          #+#    #+#             */
/*   Updated: 2022/08/10 10:39:39 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* if only one philo is at the table, it takes a fork, prints the msg
and dies waiting for the other one. Its death is dealt with by Hades, but we
need to release the fork's mutex straight away */

void	solo_banquet(t_philo *camus)
{
	pthread_mutex_lock(&camus->l_fork->f_mutex);
	print_msg(camus, " has taken a fork\n");
	pthread_mutex_unlock(&camus->l_fork->f_mutex);
	custom_usleep(camus->cigue_ti);
	return ;
}

/* Can the philos take their forks ? First they check the common Schroedinger :
if a philo had died, the process ends. Otherwise, the first philo is 
left handed while the others are right handed, to prevent mutex's dependance */
int	grab_forks(t_philo *camus)
{
	if(are_you_dead(camus))
			return (FAILURE);
	if (camus->philo_id % 2 == 1)
	{
		pthread_mutex_lock(&camus->l_fork->f_mutex);
		print_msg(camus, " has taken a fork\n");
		pthread_mutex_lock(&camus->r_fork->f_mutex);
		print_msg(camus, " has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(&camus->r_fork->f_mutex);
		print_msg(camus, " has taken a fork\n");
		pthread_mutex_lock(&camus->l_fork->f_mutex);
		print_msg(camus, " has taken a fork\n");
	}
	return (SUCCESS);
}

/* if a philo has died while some were holding their forks, those are released 
and the process terminates. Otherwise, they just put them back on the table */
int	drop_forks(t_philo *camus)
{
	if (are_you_dead(camus))
	{
		pthread_mutex_unlock(&camus->r_fork->f_mutex);
		pthread_mutex_unlock(&camus->l_fork->f_mutex);
		return (FAILURE);
	}
	if (camus->philo_id % 2 == 1)
	{
		pthread_mutex_unlock(&camus->r_fork->f_mutex);
		pthread_mutex_unlock(&camus->l_fork->f_mutex);
	}
	else
	{
		pthread_mutex_unlock(&camus->l_fork->f_mutex);
		pthread_mutex_unlock(&camus->r_fork->f_mutex);
	}
	return (SUCCESS);
}

/* checks how many times the philosopher has eaten */
int	check_meal_count(t_philo *camus)
{
	pthread_mutex_lock(&camus->root->root_mutex);

	if (camus->m_nb != 0 && camus->m_count >= camus->m_nb)
	{
		camus->root->schroedinger = 2;
	pthread_mutex_unlock(&camus->root->root_mutex);
		
		return (FAILURE);
	}
	pthread_mutex_unlock(&camus->root->root_mutex);

	return (SUCCESS);
}

/* if only one philo is at the table, the "solo_banquet" function
is executed. When a philo his holding two forks, the "# is eating"
is printed. Then the time of the start of the meal is saved in
"last_banquet" - a variable protected by the philo's own mutex.
The philo eats for the required time, although it is checked that
it doesn't die with its mouth full. The philo eventually drops his forks
The philo's meal counter is incremented by one and we check whether the philo
has eaten the required number of times */
int	ft_banquet(t_philo *camus)
{
	if (camus->root->nb_philo == 1)
	{
		solo_banquet(camus);
		return (FAILURE);
	}
	if (grab_forks(camus))
		return (FAILURE);
	print_msg(camus, " is eating\n");
	pthread_mutex_lock(&camus->c_mutex);
	camus->last_banquet = timestamp(camus);
	pthread_mutex_unlock(&camus->c_mutex);
	camus->m_count++;
	custom_usleep(camus->banquet_ti);
	if (drop_forks(camus))
		return (FAILURE);
	if (check_meal_count(camus))
		return (FAILURE);
	return (SUCCESS);
}
