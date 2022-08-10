/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 10:21:59 by elouisia          #+#    #+#             */
/*   Updated: 2022/08/10 10:40:07 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* the message is only printed if all the philo are alive by checking the 
common variable "schroedinger". If more than one philo dies, only one message 
is printed, then the variable common variable "printed" is set to 1. 
The mutex "root_mutex" protects the whole process */

void	print_msg(t_philo *camus, char *msg)
{
	pthread_mutex_lock(&camus->root->root_mutex);
	if (camus->root->schroedinger == 0)
	{
		ft_putnbr(timestamp(camus));
		write(1, " ", 1);
		ft_putnbr(camus->philo_id);
		write(1, msg, ft_strlen(msg));
	}
	if (msg[1] == 'd')
	{
		if (camus->root->printed == 0)
		{
			ft_putnbr(timestamp(camus));
			write(1, " ", 1);
			ft_putnbr(camus->philo_id);
			write(1, msg, ft_strlen(msg));
			camus->root->printed = 1;
		}
	}
	pthread_mutex_unlock(&camus->root->root_mutex);
	return ;
}