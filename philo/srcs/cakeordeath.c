/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cakeordeath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:58:16 by elouisia          #+#    #+#             */
/*   Updated: 2022/08/08 14:38:39 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Checks whether the philo has eaten before the set "cigue_time" (time_to_die).
If the difference between the timestamp and the time since its last meal is
greater than the set cigue_time, the philo dies. The common schroedinger
variable is set to 1, a msg is printed and the mutex are unlocked. */
int	cake_or_death(t_philo *camus, char *msg)
{
	// printf("cake or death - msg : %s\n", msg);
	pthread_mutex_lock(&camus->c_mutex);
	pthread_mutex_lock(&camus->root->root_mutex);
	if (msg && (timestamp(camus) - camus->last_banquet) > camus->cigue_ti)
	{
		// printf("A\n");
		pthread_mutex_unlock(&camus->c_mutex);
		camus->root->schroedinger = 1;
		print_msg(camus, " died\n");
		pthread_mutex_unlock(&camus->root->root_mutex);
		return (FAILURE);
	}
	else
	{
		// printf("B\n");
		pthread_mutex_unlock(&camus->c_mutex);
		if (msg)
			print_msg(camus, msg);
		pthread_mutex_unlock(&camus->root->root_mutex);
		return (SUCCESS);
	}
}
