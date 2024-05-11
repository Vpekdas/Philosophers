/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inf1n1ty <inf1n1ty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:08:34 by vopekdas          #+#    #+#             */
/*   Updated: 2024/05/11 02:14:52 by inf1n1ty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds, t_program *program, t_philo *philo)
{
	size_t	start;

	pthread_mutex_lock(&program->death_lock);
	if (program->is_philo_dead != 0 || philo->meal_eaten >= philo->nb_to_eat)
	{
		pthread_mutex_unlock(&program->death_lock);
		return (0);
	}
	pthread_mutex_unlock(&program->death_lock);
	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}
