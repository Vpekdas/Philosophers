/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_finish.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:33:05 by vopekdas          #+#    #+#             */
/*   Updated: 2024/05/03 17:50:54 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_death(t_philo **philos, t_program *program)
{
	size_t	start;
	size_t	i;

	start = get_current_time();
	i = 0;
	while (1)
	{
		while (i < philos[0]->philo_nb)
		{
			if (start - philos[i]->last_meal_time >= philos[i]->time_to_die)
				program->is_philo_dead = true;
			++i;
		}
		
	}
}