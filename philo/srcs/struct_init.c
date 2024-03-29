/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 10:24:54 by elouisia          #+#    #+#             */
/*   Updated: 2022/08/09 17:28:15 by elouisia         ###   ########.fr       */
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
	pthread_mutex_init(&camus->c_mutex, NULL);
	camus->root = root;
	camus->launch_time = root->start + (root->nb_philo * 10);
	camus->m_nb = root->m_nb;
	camus->cigue_ti = root->cigue_ti;
	camus->banquet_ti = root->banquet_ti;
	camus->dream_ti = root->dream_ti;
	camus->nb_philo = root->nb_philo;
	camus->m_checked = root->m_checked;
	camus->philo_id = i + 1;
	camus->fork = root->fork;
	if (i == root->nb_philo - 1)
		camus->r_fork = &root->fork[0];
	else
		camus->r_fork = &root->fork[i + 1];
	camus->l_fork = &root->fork[i];
}

/* initialisation of the main structure root*/
int	struct_init(int ac, char **av, t_root *root)
{
	memset(root, 0, sizeof(t_root));
	pthread_mutex_init(&root->root_mutex, NULL);
	root->nb_philo = (int)ft_atol(av[1]);
	if (root->nb_philo <= 0)
		return (ERROR);
	root->th = malloc(sizeof(pthread_t) * root->nb_philo);
	root->camus = malloc(sizeof(t_philo) * root->nb_philo);
	root->fork = malloc(sizeof(t_fork) * root->nb_philo);
	if (!root->camus || !root->th || !root->fork)
		return (FAILURE);
	root->start = get_time();
	root->cigue_ti = ft_atol(av[2]);
	root->banquet_ti = ft_atol(av[3]);
	root->dream_ti = ft_atol(av[4]);
	if (ac == 6)
	{
		root->m_nb = ft_atol(av[5]);
		root->m_checked = 1;
	}
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
