/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 10:13:20 by elouisia          #+#    #+#             */
/*   Updated: 2022/08/05 17:03:06 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	fork_init(t_root *root)
{
	int	i;

	i = 0;
	while (i < root->nb_philo)
	{
		pthread_mutex_init(&root->fork[i].f_mutex, NULL);
		i++;
	}
}

void	philo_init(t_philo *camus, int i, t_root *root)
{
	memset(camus, 0, sizeof(t_philo));
	camus->root = root;
	camus->philo_id = i + 1;
	camus->fork = root->fork;
	if (i == root->nb_philo - 1)
		camus->r_fork = &root->fork[0];
	else
		camus->r_fork = &root->fork[i + 1];
	camus->l_fork = &root->fork[i];
	camus->start = get_time();
	camus->m_nb = root->m_nb;
	camus->cigue_ti = root->cigue_ti;
	camus->banquet_ti = root->banquet_ti;
	camus->dream_ti = root->dream_ti;
	camus->nb_philo = root->nb_philo;
	camus->launch_time = root->launch_time;
}

/* initialisation of the main structure root*/
int	struct_init(int ac, char **av, t_root *root)
{
	memset(root, 0, sizeof(t_root));
	pthread_mutex_init(&root->root_mutex, NULL);
	root->nb_philo = (int)ft_atol(av[1]);
	root->launch_time = (get_time() + 500);
	if (root->nb_philo <= 0 || root->nb_philo > 200)
		return (ERROR);
	root->th = malloc(sizeof(pthread_t) * root->nb_philo);
	if (!root->th)
		return (FAILURE);
	root->camus = malloc(sizeof(t_philo) * root->nb_philo);
	if (!root->camus)
		return (FAILURE);
	root->fork = malloc(sizeof(t_fork) * root->nb_philo);
	if (!root->fork)
		return (FAILURE);
	root->cigue_ti = ft_atol(av[2]);
	root->banquet_ti = ft_atol(av[3]);
	root->dream_ti = ft_atol(av[4]);
	if (ac == 6)
		root->m_nb = ft_atol(av[5]);
	if (check_numbers(root, ac))
		return (ERROR);
	return (SUCCESS);
}

/* initialisation of the forks' and philos' structures */
int	ft_init(int ac, char **av, t_root *root)
{
	int	i;

	i = struct_init(ac, av, root);
	if (i == ERROR)
	{
		printf("You do not want to break my program.\
 You want to go home and rethink your life.\n");
		return (FAILURE);
	}
	else if (i == FAILURE)
		return (FAILURE);
	fork_init(root);
	i = 0;
	while (i < root->nb_philo)
	{
		philo_init(&root->camus[i], i, root);
		i++;
	}
	return (SUCCESS);
}
