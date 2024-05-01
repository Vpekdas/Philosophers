/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_msg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inf1n1ty <inf1n1ty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:23:29 by inf1n1ty          #+#    #+#             */
/*   Updated: 2024/05/02 01:05:38 by inf1n1ty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	argc_error(int ac)
{
	char	*argc;

	argc = ft_itoa(ac - 1);
	ft_putstr_fd(RED"Error: Incorrect number of arguments", 2);
	ft_putstr_fd("(", 2);
	ft_putstr_fd(argc, 2);
	ft_putstr_fd(")\n", 2);
	ft_putstr_fd("Usage: ./philo number_of_philosophers | ", 2);
	ft_putstr_fd("time_to_die | time_to_eat | ", 2);
	ft_putstr_fd("time_to_sleep | ", 2);
	ft_putstr_fd("[number_of_times_each_philosopher_must_eat\n"NC, 2);
	free(argc);
}
