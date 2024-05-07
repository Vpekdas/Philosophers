/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:10:18 by vopekdas          #+#    #+#             */
/*   Updated: 2024/05/07 13:54:18 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_philo	**init_philo_struct(char **av)
{
	size_t	i;
	t_philo	**philos;

	i = 0;
	philos = NULL;
	philos = ft_calloc(ft_atoi(av[1]), sizeof(t_philo *));
	if (!philos)
		return (NULL);
	while (i < ft_atoi(av[1]))
	{
		philos[i] = ft_calloc(1, sizeof(t_philo));
		if (!philos[i])
			return (NULL);
		++i;
	}
	return (philos);
}

void	fill_parsing(int ac, char **av, t_philo **philos, t_program *program)
{
	size_t	i;

	i = 0;
	program->start = get_current_time();
	while (i < ft_atoi(av[1]))
	{
		philos[i]->program = program;
		philos[i]->philo_id = i + 1;
		philos[i]->philo_nb = ft_atoi(av[1]);
		philos[i]->time_to_die = ft_atoi(av[2]);
		philos[i]->time_to_eat = ft_atoi(av[3]);
		philos[i]->time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			philos[i]->nb_to_eat = ft_atoi(av[5]);
		else
			philos[i]->nb_to_eat = -1;
		++i;
	}
}

int	create_thread(t_philo **philos, void *routine)
{
	size_t	i;

	i = 0;
	while (i < philos[0]->philo_nb)
	{
		if (pthread_create(&philos[i]->thread, NULL, routine, philos[i]) != 0)
			return (ERROR_INIT_THREAD);
		++i;
	}
	return (OK);
}

static void	assign_forks(t_philo **philos, size_t philo_nb, t_program *program)
{
	size_t	i;

	i = 0;
	while (i < philo_nb)
	{
		philos[i]->r_fork = &program->forks[i];
		philos[i]->l_fork = &program->forks[(i + philo_nb - 1) % philo_nb];
		++i;
	}
}

int	create_forks(size_t philo_nb, t_program *program)
{
	size_t	i;

	i = 0;
	program->forks = ft_calloc(philo_nb, sizeof(pthread_mutex_t));
	if (!program->forks)
		return (ERROR_CALLOC);
	while (i < philo_nb)
	{
		if (pthread_mutex_init(&program->forks[i], NULL) != 0)
			return (ERROR_INIT_MUTEX);
		++i;
	}
	if (pthread_mutex_init(&program->global_lock, NULL) != 0)
		return (ERROR_INIT_MUTEX);
	assign_forks(program->philos, philo_nb, program);
	return (OK);
}
