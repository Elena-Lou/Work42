/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cakeordeath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:58:16 by elouisia          #+#    #+#             */
/*   Updated: 2022/08/05 15:33:46 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Checks whether the philo has eaten before the set "cigue_time" (time_to_die).
If the difference between the timestamp and the time since its last meal is
greater than the set cigue_time, the philo dies. The common schroedinger
variable is set to 1, a msg is printed and the mutex are unlocked. */
int	cake_or_death(t_philo *camus)
{
	pthread_mutex_lock(&camus->root->root_mutex);
	if (camus->root->schroedinger == 1)
	{
		pthread_mutex_unlock(&camus->root->root_mutex);
		return (FAILURE);
	}
	else if ((timestamp(camus) - camus->last_banquet) > camus->cigue_ti)
	{
		camus->root->schroedinger = 1;
		pthread_mutex_unlock(&camus->root->root_mutex);
		print_msg(camus, "died\n");
		return (FAILURE);
	}
	else
	{
		pthread_mutex_unlock(&camus->root->root_mutex);
		return (SUCCESS);
	}
}
