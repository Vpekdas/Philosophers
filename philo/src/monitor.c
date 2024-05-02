/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inf1n1ty <inf1n1ty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 00:03:47 by inf1n1ty          #+#    #+#             */
/*   Updated: 2024/05/03 00:18:40 by inf1n1ty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*monitor(t_program *program)
{
	size_t	i;
	size_t	time_diff;

	while (1)
	{
		i = 0;
		while (i < program->philos[0]->philo_nb)
		{
			pthread_mutex_lock(&program->philos[i]->meal_lock);
			time_diff = get_current_time() - program->philos[i]->last_meal_time;
			pthread_mutex_unlock(&program->philos[i]->meal_lock);
			if (time_diff >= program->philos[i]->time_to_die)
			{
				program->philos[i]->is_philo_dead = true;
				print_message(DIED, program->philos[i]);
				return (NULL);
			}
			++i;
		}
		usleep(1000);
	}
	return (NULL);
}