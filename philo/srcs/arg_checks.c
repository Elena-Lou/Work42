/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 10:31:23 by elouisia          #+#    #+#             */
/*   Updated: 2022/08/05 08:18:02 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* check that all the numbers given will are strictly positive and no bigger
				than INT_MAX */
int	check_numbers(t_root *root, int ac)
{
	if (root->nb_philo <= 0)
		return (FAILURE);
	if (root->cigue_ti > 2147483647)
		return (FAILURE);
	if (root->banquet_ti > 2147483647)
		return (FAILURE);
	if (root->dream_ti > 2147483647)
		return (FAILURE);
	if (ac == 6)
	{
		if (root->m_nb <= 0 || root->m_nb > 2147483647)
			return (FAILURE);
	}
	return (SUCCESS);
}

/*check that the arguments are nothing but numbers*/
int	arg_checks(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (ac < 5 || ac > 6)
	{
		printf("Usage: ./philo nb_of_philo time_to_die time_to_eat \
time_to_sleep [nb of times to eat]\n");
		return (FAILURE);
	}
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_isdigit(av[i][j]) == 0)
				return (ERROR);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
