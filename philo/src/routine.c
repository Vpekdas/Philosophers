/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:10:48 by vopekdas          #+#    #+#             */
/*   Updated: 2024/05/04 19:00:40 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	lock_unlock_fork(enum e_fork fork, t_philo *philo)
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

static void	eat_and_sleep(t_philo *philo)
{
	lock_unlock_fork(LOCK, philo);
	print_message(EATING, philo);
	pthread_mutex_lock(&philo->program->global_lock);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->program->global_lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_lock(&philo->program->global_lock);
	philo->meal_eaten++;
	pthread_mutex_unlock(&philo->program->global_lock);
	lock_unlock_fork(UNLOCK, philo);
	print_message(SLEEPING, philo);
	ft_usleep(philo->time_to_sleep);
}

void	*routine(t_philo *philo)
{
	if (philo->philo_nb == 1)
	{
		ft_usleep(philo->time_to_die);
		return (NULL);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->program->global_lock);
		if (philo->meal_eaten == philo->nb_to_eat
			|| philo->program->is_philo_dead)
		{
			pthread_mutex_unlock(&philo->program->global_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->program->global_lock);
		eat_and_sleep(philo);
		print_message(THINKING, philo);
	}
	return (NULL);
}
