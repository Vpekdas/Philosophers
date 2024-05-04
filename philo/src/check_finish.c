/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_finish.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:33:05 by vopekdas          #+#    #+#             */
/*   Updated: 2024/05/04 18:11:32 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	check_death(t_philo **philos, t_program *program)
{
	size_t	i;
	size_t	current;

	i = 0;
	ft_usleep(philos[0]->time_to_die + 10);
	while (i < philos[0]->philo_nb)
	{
		pthread_mutex_lock(&program->global_lock);
		current = get_current_time();
		if (current - philos[i]->last_meal_time > philos[i]->time_to_die)
		{
			program->is_philo_dead = philos[i]->philo_id;
			pthread_mutex_unlock(&program->global_lock);
			return ;
		}
		pthread_mutex_unlock(&program->global_lock);
		++i;
	}
}

static bool	check_if_enough_meals(t_philo **philos)
{
	size_t	i;

	i = 0;
	while (i < philos[0]->philo_nb)
	{
		pthread_mutex_lock(&philos[i]->program->global_lock);
		if (philos[i]->meal_eaten < philos[i]->nb_to_eat)
		{
			pthread_mutex_unlock(&philos[i]->program->global_lock);
			return (false);
		}
		pthread_mutex_unlock(&philos[i]->program->global_lock);
		++i;
	}
	return (true);
}

void	end_loop(t_philo **philos, t_program *program)
{
	while (1)
	{
		if (check_if_enough_meals(philos) == true)
			break ;
		check_death(philos, program);
		if (program->is_philo_dead != 0)
		{
			print_message(DIED, philos[program->is_philo_dead - 1]);
			break ;
		}
	}
}
