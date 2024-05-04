#include "../include/philo.h"

void	join_thread(t_philo **philos, size_t philo_nb)
{
	size_t	i;

	i = 0;
	while (i < philo_nb)
	{
		pthread_join(philos[i]->thread, NULL);
		++i;
	}
}

// void	free_struct(t_philo **philos, t_program *program)
// {

// }