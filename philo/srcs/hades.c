/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hades.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:02:23 by elouisia          #+#    #+#             */
/*   Updated: 2022/08/05 16:02:32 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Hades, the death supervisor. Runs parallel to the threads and loops over 
the different cases which could end a philo's life and might have been
overlooked by the threads : last_meal > cigue_time / number of meals eaten /
one philo dead */

void	are_you_dead(t_philo *camus, int i)
{
	while (get_time() < camus->root->launch_time)
		usleep(10);
	while (1)
	{
		i = 0;
		while (i < camus->nb_philo)
		{
			if (cake_or_death(&camus[i]))
			{
				printf("KILLED BY HADES %u\n", timestamp(&camus[i]));
				return ;
			}
			pthread_mutex_lock(&camus->root->root_mutex);
			if (camus->root->schroedinger == 1)
			{
				printf("KILLED BY HADES BIS %u\n", timestamp(&camus[i]));
				pthread_mutex_unlock(&camus->root->root_mutex);
				print_msg(&camus[i], "died\n");
				return ;
			}
			if (camus->m_nb != 0 && camus->m_count >= camus->m_nb)
			{
				pthread_mutex_unlock(&camus->root->root_mutex);
				return ;
			}
			pthread_mutex_unlock(&camus->root->root_mutex);
			i++;
		}
		usleep(50);
	}
}
