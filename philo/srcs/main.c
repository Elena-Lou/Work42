/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:06:26 by elouisia          #+#    #+#             */
/*   Updated: 2022/08/09 18:06:01 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* the threads are created with a slight delay for the evenly numbered ones,
Hades is launched after their creation and runs in a infinite loop.
Once it stops, the threads are joined to the main process - thus terminating */
// int	delayed_launch(t_philo *camus)
// {
// 	int	i;

// 	i = 0;
// 	while (i < camus->root->nb_philo)
// 	{
// 		if (i % 2 == 0)
// 			pthread_create(camus->root->th + i, NULL, &ft_routine,
// 				&camus->root->camus[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < camus->root->nb_philo)
// 	{
// 		if (i % 2 == 1)
// 		{
// 			custom_usleep(10);
// 			pthread_create(camus->root->th + i, NULL, &ft_routine,
// 				&camus->root->camus[i]);
// 		}
// 		i++;
// 	}
	// hades(camus, i);
// 	return (SUCCESS);
// }
int	join_threads(t_root *root)
{
	int	i;
	
	i = 0;
	while (i < root->nb_philo)
	{
		pthread_join(root->th[i], NULL);
		i++;
	}
	return (SUCCESS);
}

int	delayed_launch(t_philo *camus)
{
	int	i;

	i = 0;
	while (i < camus->root->nb_philo)
	{
		pthread_create(camus->root->th + i, NULL, &ft_routine,
		&camus->root->camus[i]);
		i++;
	}
	hades(camus, i);
	return (SUCCESS);
}

void	mutex_destroyer(t_root *root)
{
	int	i;

	i = 0;
	while (i < root->nb_philo)
	{
		pthread_mutex_destroy(&root->fork[i].f_mutex);
		i++;
	}
	pthread_mutex_destroy(&root->root_mutex);
	free(root->th);
	free(root->camus);
	free(root->fork);
}

int	main(int ac, char **av)
{
	t_root			root;
	int				i;

	i = arg_checks(ac, av);
	if (i == ERROR)
	{
		printf("You do not want to break my program.\
 You want to go home and rethink your life.\n");
		return (FAILURE);
	}
	else if (i == FAILURE)
		return (FAILURE);
	if (ft_init(ac, av, &root))
		return (FAILURE);
	delayed_launch(root.camus);
	i = 0;
	while (i < root.nb_philo)
	{
		pthread_join(root.th[i], NULL);
		i++;
	}		
	mutex_destroyer(&root);
	return (SUCCESS);
}
