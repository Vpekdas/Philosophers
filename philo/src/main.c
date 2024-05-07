/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:23:33 by vopekdas          #+#    #+#             */
/*   Updated: 2024/05/07 11:57:13 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_philo		**philos;
	t_program	program;

	philos = NULL;
	program = (t_program){0};
	if (ac == 5 || ac == 6)
	{
		if (overall_parsing_check(ac, av) == ERROR)
			return (free_struct(philos, &program, ERROR));
		philos = init_philo_struct(av);
		if (!philos)
			return (free_struct(philos, &program, ERROR_CALLOC));
		program.philos = philos;
		fill_parsing(ac, av, philos, &program);
		if (create_forks(philos[0]->philo_nb, &program) == ERROR_INIT_MUTEX)
			return (free_struct(philos, &program, ERROR_INIT_MUTEX));
		if (create_thread(philos, routine) == ERROR_INIT_THREAD)
			return (free_struct(philos, &program, ERROR_INIT_THREAD));
		end_loop(philos, &program);
		join_thread(philos, philos[0]->philo_nb);
		free_struct(philos, &program, OK);
	}
	else
		argc_error(ac);
}
