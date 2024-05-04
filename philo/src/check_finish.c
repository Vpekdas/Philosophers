/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_finish.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:33:05 by vopekdas          #+#    #+#             */
/*   Updated: 2024/05/04 15:43:40 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_death(t_philo **philos, t_program *program)
{
	size_t	i;

	while (1)
	{
		ft_usleep(1000);
		i = 0;
		while (i < philos[0]->philo_nb)
		{
			pthread_mutex_lock(&program->global_lock);
			if (get_current_time() - philos[i]->last_meal_time > philos[i]->time_to_die)
			{
			    program->is_philo_dead = true;
			    pthread_mutex_unlock(&program->global_lock);
			    return;
			}
			pthread_mutex_unlock(&program->global_lock);
			++i;
		}
	}
}
