/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inf1n1ty <inf1n1ty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:10:48 by vopekdas          #+#    #+#             */
/*   Updated: 2024/05/03 00:03:12 by inf1n1ty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	lock_unlock_fork(enum e_fork fork, t_philo *philo)
{
	if (fork == LOCK)
	{
		if (philo->philo_id % 2 == 0)
		{
			pthread_mutex_lock(philo->r_fork);
			print_message(TAKEN_A_FORK, philo);
			pthread_mutex_lock(philo->l_fork);
			print_message(TAKEN_A_FORK, philo);
		}
		else
		{			
			pthread_mutex_lock(philo->l_fork);
			print_message(TAKEN_A_FORK, philo);
			pthread_mutex_lock(philo->r_fork);
			print_message(TAKEN_A_FORK, philo);
		}
	}
	else if (fork == UNLOCK)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
}

void	eat_and_sleep(t_philo *philo)
{
	lock_unlock_fork(LOCK, philo);
	print_message(EATING, philo);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->meal_lock);
	lock_unlock_fork(UNLOCK, philo);
	print_message(SLEEPING, philo);
	usleep(philo->time_to_sleep * 1000);
}

void	*routine(t_philo *philo)
{
	philo->start_time = get_current_time();
	while (philo->is_philo_dead == false)
	{
		eat_and_sleep(philo);
		print_message(THINKING, philo);
	}
	return (NULL);
}