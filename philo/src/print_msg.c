/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:10:36 by vopekdas          #+#    #+#             */
/*   Updated: 2024/05/04 16:18:52 by vopekdas         ###   ########.fr       */
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

void	print_message(enum e_state state, t_philo *philo)
{
	size_t	start;
	size_t	time_diff;
	size_t	id;

	start = philo->program->start;
	time_diff = get_current_time() - start;
	pthread_mutex_lock(&philo->program->global_lock);
	id = philo->philo_id;
	if (state == EATING)
		printf(ORANGE"%zu %zu is 🍝eating🍝\n"NC, time_diff, id);
	else if (state == SLEEPING)
		printf(BLUE"%zu %zu is 💤sleeping💤\n"NC, time_diff, id);
	else if (state == THINKING)
		printf(WHITE"%zu %zu is 💭thinking💭\n"NC, time_diff, id);
	else if (state == TAKEN_A_FORK)
		printf(YELLOW"%zu %zu has taken a 🍴fork🍴\n"NC, time_diff, id);
	else if (state == TAKEN_A_FORK)
		printf(PURPLE"%zu %zu has 💀died💀\n"NC, time_diff, id);
	pthread_mutex_unlock(&philo->program->global_lock);
}
