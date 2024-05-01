/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inf1n1ty <inf1n1ty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:23:33 by vopekdas          #+#    #+#             */
/*   Updated: 2024/05/02 00:45:26 by inf1n1ty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_philo	**philos;

	philos = NULL;
	if (ac == 5 || ac == 6)
	{
		if (overall_parsing_check(ac, av) == ERROR)
			return (ERROR);
		if (init_struct(av, philos) == ERROR_CALLOC)
			return (ERROR);
	}
	else
		argc_error(ac);
}

// TODO: create proper function to free depending on error code.
