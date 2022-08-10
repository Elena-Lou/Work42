/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_you_dead.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:58:16 by elouisia          #+#    #+#             */
/*   Updated: 2022/08/09 17:05:03 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	are_you_dead(t_philo *camus)
{
	pthread_mutex_lock(&camus->root->root_mutex);
	if (camus->root->schroedinger == 1)
	{
		pthread_mutex_unlock(&camus->root->root_mutex);
		return (FAILURE);
	}
	pthread_mutex_unlock(&camus->root->root_mutex);
	return (SUCCESS);
}
