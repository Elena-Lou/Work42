/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 10:22:55 by elouisia          #+#    #+#             */
/*   Updated: 2022/08/08 14:47:23 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

unsigned int	timestamp(t_philo *camus)
{
	unsigned int	stamp;

	stamp = get_time() - camus->launch_time;
	return (stamp);
}

/* usleep function which checks whether a philo dies in its sleep */
int	custom_usleep_death(t_philo *camus, unsigned int t)
{
	unsigned int	start;
	unsigned int	end;

	start = timestamp(camus);
	end = start + t;
	while (timestamp(camus) < end)
	{
		if (cake_or_death(camus, NULL))
			return (FAILURE);
		usleep(10);
	}
	return (SUCCESS);
}

void	custom_usleep(unsigned int t)
{
	unsigned int	start;
	unsigned int	end;

	start = get_time();
	end = start + t;
	while (get_time() < end)
		usleep(10);
	return ;
}
