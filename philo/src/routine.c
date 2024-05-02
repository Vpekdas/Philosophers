/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:10:48 by vopekdas          #+#    #+#             */
/*   Updated: 2024/05/02 15:34:49 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	think(t_philo *philo)
{
	size_t	start;

	start = philo->start_time;
	pthread_mutex_lock(&philo->program->write_lock);
	printf("%zu %zu is thinking\n", get_current_time() - start, philo->philo_id);
	pthread_mutex_unlock(&philo->program->write_lock);
}

void	*routine(t_philo *philo)
{
	philo->start_time = get_current_time();
	while (1)
	{
		think(philo);
	}
}