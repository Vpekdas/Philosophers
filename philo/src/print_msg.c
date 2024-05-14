/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:10:36 by vopekdas          #+#    #+#             */
/*   Updated: 2024/05/14 17:13:54 by vopekdas         ###   ########.fr       */
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
	ft_putstr_fd("Usage: ./philo | ", 2);
	ft_putstr_fd(RED"number_of_philosophers | ", 2);
	ft_putstr_fd(BLUE"time_to_die | ", 2);
	ft_putstr_fd(PURPLE"time_to_eat | ", 2);
	ft_putstr_fd(CYAN"time_to_sleep | ", 2);
	ft_putstr_fd(YELLOW"number_of_times_each_philosopher_must_eat\n"NC, 2);
	free(argc);
}

void	print_message(enum e_state state, t_philo *philo)
{
	size_t	start;
	size_t	time_diff;
	size_t	id;

	start = philo->program->start;
	time_diff = get_current_time() - start;
	id = philo->philo_id;
	pthread_mutex_lock(&philo->program->death_lock);
	if (state == EATING && philo->program->is_philo_dead == 0)
		printf(ORANGE"%zu %zu is 🍝 eating 🍝\n"NC, time_diff, id);
	else if (state == SLEEPING && philo->program->is_philo_dead == 0)
		printf(BLUE"%zu %zu is 💤 sleeping 💤\n"NC, time_diff, id);
	else if (state == THINKING && philo->program->is_philo_dead == 0)
		printf(WHITE"%zu %zu is 💭 thinking 💭\n"NC, time_diff, id);
	else if (state == TAKEN_A_FORK && philo->program->is_philo_dead == 0)
		printf(YELLOW"%zu %zu has taken a 🍴 fork 🍴\n"NC, time_diff, id);
	else if (state == DIED)
		printf(PURPLE"%zu %zu 💀 died 💀\n"NC, time_diff, id);
	else if (state == MEAL)
		printf(GREEN"%zu 🥣 all philosophears eat 🥣 \n"NC, time_diff);
	pthread_mutex_unlock(&philo->program->death_lock);
}
