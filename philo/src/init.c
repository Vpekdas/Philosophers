/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inf1n1ty <inf1n1ty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 00:41:30 by inf1n1ty          #+#    #+#             */
/*   Updated: 2024/05/02 01:07:22 by inf1n1ty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_struct(char **av, t_philo **philos)
{
	int	i;

	i = 0;
	philos = ft_calloc(ft_atoi(av[1]), sizeof(t_philo *));
	if (!philos)
		return (ERROR_CALLOC);
	while (i < ft_atoi(av[1]))
	{
		philos[i] = ft_calloc(1, sizeof(t_philo));
		if (!philos[i])
			return (ERROR_CALLOC);
		++i;
	}
	return (OK);
}

int	create_thread(t_philo **philos, size_t philo_nb, void *routine)
{
	size_t	i;

	i = 0;
	while (i < philo_nb)
	{
		if (pthread_create(&philos[i]->thread, NULL, routine, philos[i]) != 0)
			return (ERROR_INIT_THREAD);
		++i;
	}
	return (OK);
}

int	create_forks(size_t philo_nb, t_program *program)
{
	size_t	i;

	i = 0;
	program->forks = ft_calloc(philo_nb, sizeof(pthread_mutex_t *));
	if (!program->forks)
		return (ERROR_CALLOC);
	while (i < philo_nb)
	{
		if (pthread_mutex_init(&program->forks[i], NULL) != 0)
			return (ERROR_INIT_MUTEX);
		++i;
	}
	return (OK);
}

void	fill_time_and_philo(int ac, char **av, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
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

void	assign_forks(t_philo **philos, size_t philo_nb, t_program *program)
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
