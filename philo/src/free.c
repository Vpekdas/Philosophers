/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:11:47 by vopekdas          #+#    #+#             */
/*   Updated: 2024/05/05 15:32:56 by vopekdas         ###   ########.fr       */
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

int	free_struct(t_philo **philos, t_program *program)
{
	size_t	i;
	size_t	philo_nb;

	i = 0;
	philo_nb = philos[0]->philo_nb;
	if (program->forks)
	{
		free(program->forks);
		program->forks = NULL;
	}
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
	return (OK);
}
