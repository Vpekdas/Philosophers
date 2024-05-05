/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_finish.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:33:05 by vopekdas          #+#    #+#             */
/*   Updated: 2024/05/05 15:31:00 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

static int	check_death(t_philo **philos, t_program *program)
{
	size_t	i;
	size_t	current;

	i = 0;
	if (ft_usleep(philos[0]->time_to_die, program) == ERROR_SLEEP)
		return (ERROR_SLEEP);
	while (i < philos[0]->philo_nb)
	{
		pthread_mutex_lock(&program->global_lock);
		current = get_current_time();
		if (current - philos[i]->last_meal_time >= philos[i]->time_to_die)
		{
			program->is_philo_dead = philos[i]->philo_id;
			pthread_mutex_unlock(&program->global_lock);
			return (OK);
		}
		pthread_mutex_unlock(&program->global_lock);
		++i;
	}
	return (OK);
}

void	end_loop(t_philo **philos, t_program *program)
{
	while (1)
	{
		if (check_death(philos, program) == ERROR_SLEEP)
			return ;
		if (program->is_philo_dead != 0 && !check_if_enough_meals(philos))
		{
			print_message(DIED, philos[program->is_philo_dead - 1]);
			break ;
		}
		if (check_if_enough_meals(philos) == true)
		{
			print_message(MEAL, philos[0]);
			break ;
		}
	}
}
