/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 16:59:24 by elouisia          #+#    #+#             */
/*   Updated: 2022/08/10 10:47:45 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* The time for each philo before they can grab a fork. We check if all the
philos are safe and sound, then we check their cigue_time. */
int	ft_think(t_philo *camus)
{
	if (are_you_dead(camus))
		return (FAILURE);
	print_msg(camus, " is thinking\n");
	if (camus->nb_philo % 2 == 1)
		custom_usleep(camus->cigue_ti * 0.2);
	return (SUCCESS);
}

/* The time for each philo to rest and digest after their banquet. 
We check if all the philos are safe and sound, then we check their cigue_time.
While they sleep, we use a customed sleep function which slighlty increments 
their sleeping time to constantly check if they do not die of starvation in 
their sleep */
int	ft_dream(t_philo *camus)
{
	if (are_you_dead(camus))
		return (FAILURE);
	print_msg(camus, " is sleeping\n");
	custom_usleep(camus->dream_ti);
	return (SUCCESS);
}

void	set_groups(t_philo *camus)
{
	if (camus->philo_id % 3 == 1)
		custom_usleep(camus->banquet_ti);
	if (camus->philo_id % 3 == 2)
		custom_usleep(camus->banquet_ti * 2);
		
}

/* the philosophers daily_routine which runs in a loop, unless one dies*/
int	ft_daily_routine(t_philo *camus)
{
	if (camus->nb_philo % 2 == 1)
		set_groups(camus);
	if (camus->philo_id % 2 == 0)
		custom_usleep(200);
	while (1)
	{
		if (are_you_dead(camus))
			return (FAILURE);
		if (ft_banquet(camus))
			return (FAILURE);
		if (ft_dream(camus))
			return (FAILURE);
		if (ft_think(camus))
			return (FAILURE);
	}
	return (FAILURE);
}

void	*ft_routine(void *void_camus)
{
	t_philo	*camus;

	camus = (t_philo *)void_camus;
	while (get_time() < camus->launch_time)
		usleep(50);
	while (!ft_daily_routine(camus))
		return (NULL);
	return (NULL);
}
