/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hades.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:02:23 by elouisia          #+#    #+#             */
/*   Updated: 2022/08/10 10:39:08 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Checks whether the philo has eaten before the set "cigue_time" (time_to_die).
If the difference between the timestamp and the time since its last meal is
greater than the set cigue_time, the philo dies. The common schroedinger
variable is set to 1, a msg is printed and the mutex are unlocked. */
int	cake_or_death(t_philo *camus)
{
	pthread_mutex_lock(&camus->c_mutex);
	pthread_mutex_lock(&camus->root->root_mutex);
	if ((timestamp(camus) - camus->last_banquet) > camus->cigue_ti)
	{
		pthread_mutex_unlock(&camus->c_mutex);
		camus->root->schroedinger = 1;
		pthread_mutex_unlock(&camus->root->root_mutex);
		print_msg(camus, " died\n");
		return (FAILURE);
	}
	else if (camus->root->schroedinger == 2)
	{
		
		pthread_mutex_unlock(&camus->c_mutex);
		pthread_mutex_unlock(&camus->root->root_mutex);
		return (FAILURE);
		
	}
	else
	{
		pthread_mutex_unlock(&camus->c_mutex);
		pthread_mutex_unlock(&camus->root->root_mutex);
		return (SUCCESS);
	}
}

/* Hades, the death supervisor. Runs parallel to the threads and loops over 
the different cases which could end a philo's life and might have been
overlooked by the threads : last_meal > cigue_time / number of meals eaten /
one philo dead */
int	hades(t_philo *camus, int i)
{
	while (get_time() < camus->launch_time)
		usleep(10);
	while (1)
	{
		i = 0;
		while (i < camus->nb_philo)
		{
			if (cake_or_death(&camus[i]))
			{
				printf("KILLED BY HADES %u\n", timestamp(&camus[i]));
				// print_msg(&camus[i], " died\n");
				return (FAILURE) ;
			}
			i++;
		}
		usleep(50);
	}
	return (SUCCESS);
}
