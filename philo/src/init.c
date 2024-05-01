/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inf1n1ty <inf1n1ty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 00:41:30 by inf1n1ty          #+#    #+#             */
/*   Updated: 2024/05/01 02:28:59 by inf1n1ty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	fill_info(int ac, char **av, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philo->philo_nb = ft_atoi(av[1]);
		philo->time_to_die = ft_atoi(av[2]);
		philo->time_to_eat = ft_atoi(av[3]);
		philo->time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			philo->nb_to_eat = ft_atoi(av[5]);
		else
			philo->nb_to_eat = -1;
		++i;
	}
}
