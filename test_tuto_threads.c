#include <unistd.h>
#include <stdio.h>
#include <pthread.h>


typedef struct s_root
{
	// struct timeval	time;
	pthread_mutex_t mutex;
	pthread_t		*th;
	int				k;
	int				nb_philo;
}	t_root;


char * HELLO_MSG;

void	*blahblah(void *a_root)
{
	t_root *root;
	
	root = (t_root *)a_root;
	HELLO_MSG = "Hello World!";
	// sleep(5);
	pthread_mutex_lock(&root->mutex);
	root->k = 1;
	pthread_mutex_unlock(&root->mutex);
	return NULL;
}

void *blah(void *a_root)
{
	t_root *root;
	int		i;

	i = 0;
	root = (t_root *)a_root;
	while (1)
	{
		pthread_mutex_lock(&root->mutex);
		if (root->k != 0)
		{
			while (i < 13)
			{
				printf("\n%c\n", HELLO_MSG[i]);
				i++;
			}
			return NULL;
		}
		pthread_mutex_unlock(&root->mutex);
		usleep(200);
	}
	return NULL;
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_root	root;
	pthread_t	t1;
	pthread_t	t2;

	root.k = 0;
	// printf("time : %d", gettimeofday(&root.time, NULL));
	pthread_mutex_init(&root.mutex, NULL);
	pthread_create(&t1, NULL, blahblah, &root);
	pthread_create(&t2, NULL, blah, &root);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	pthread_mutex_destroy(&root.mutex);
	return (0);
}