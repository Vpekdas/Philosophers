/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inf1n1ty <inf1n1ty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:23:33 by vopekdas          #+#    #+#             */
/*   Updated: 2024/05/04 23:59:08 by inf1n1ty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_philo		**philos;
	t_program	program;
	size_t		philo_nb;

	philos = NULL;
	program = (t_program){0};
	if (ac == 5 || ac == 6)
	{
		if (overall_parsing_check(ac, av) == ERROR)
			return (ERROR);
		philos = init_philo_struct(av);
		if (!philos)
			return (ERROR_CALLOC);
		program.philos = philos;
		fill_parsing(ac, av, philos, &program);
		philo_nb = ft_atoi(av[1]);
		if (create_forks(philo_nb, &program) == ERROR_INIT_MUTEX)
			return (ERROR);
		assign_forks(philos, philo_nb, &program);
		if (create_thread(philos, routine) == ERROR_INIT_THREAD)
			return (ERROR);
		end_loop(philos, &program);
		for (size_t i = 0; i < philo_nb; i++)
			pthread_join(philos[i]->thread, NULL);
	}
	else
		argc_error(ac);
}
