/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:11:47 by vopekdas          #+#    #+#             */
/*   Updated: 2024/05/07 11:57:33 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	join_thread(t_philo **philos, size_t philo_nb)
{
	size_t	i;

	i = 0;
	while (i < philo_nb)
	{
		if (pthread_join(philos[i]->thread, NULL) != 0)
			return ;
		++i;
	}
}

static	void	free_philos(t_philo **philos, size_t philo_nb)
{
	size_t	i;

	i = 0;
	while (i < philo_nb)
	{
		if (philos[i])
		{
			free(philos[i]);
			philos[i] = NULL;
		}
		++i;
	}
	if (philos)
	{
		free(philos);
		philos = NULL;
	}
}

int	free_struct(t_philo **philos, t_program *program, int error)
{
	size_t	i;
	size_t	philo_nb;

	i = 0;
	if (!philos)
		return (ERROR_CALLOC);
	philo_nb = philos[0]->philo_nb;
	if (program->forks)
	{
		free(program->forks);
		program->forks = NULL;
	}
	free_philos(philos, philo_nb);
	return (error);
}
