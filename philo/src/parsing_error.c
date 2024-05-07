/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:20:38 by vopekdas          #+#    #+#             */
/*   Updated: 2024/05/07 13:58:07 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static int	ft_skip_zero(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == '0' && (str[i + 1]) && (str[i + 1]) == '0')
		i++;
	return (i);
}

static bool	is_arg_only_pos_nb(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < ac)
	{
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]) && av[i][j] != '+')
				return (false);
			j++;
		}
		j = 0;
		i++;
	}
	return (true);
}

static bool	is_arg_overflow_underflow(int ac, char **av)
{
	t_overflow	over;

	over = (t_overflow){0};
	over.i = 1;
	over.j = 0;
	while (over.i < ac)
	{
		if (ft_atoi(av[over.i]) == 0)
			return (true);
		over.str = ft_itoa(ft_atoi(av[over.i]));
		if (!over.str)
			return (true);
		over.arg = av[over.i];
		if (*over.arg == '-' && over.str[over.j++] == '-')
			over.arg++;
		while (*over.arg && *over.arg == '0' && ft_strlen(over.arg) > 1)
			over.arg++;
		over.j += ft_skip_zero(over.str);
		if (ft_strcmp(over.arg, over.str + over.j) != 0)
			return (free(over.str), true);
		free(over.str);
		over.j = 0;
		over.i++;
	}
	return (false);
}

int	overall_parsing_check(int ac, char **av)
{
	if (is_arg_only_pos_nb(ac, av) == false)
	{
		ft_putstr_fd(RED"🤗 Error: Only positive numbers are allowed.🤗\n" NC, 2);
		return (ERROR);
	}
	if (is_arg_overflow_underflow(ac, av) == true)
	{
		ft_putstr_fd(RED"🚱 Error: Please enter numbers within" NC, 2);
		ft_putstr_fd(RED" the size_t range, excluding 0.🚱\n", 2);
		return (ERROR);
	}
	if (ft_atoi(av[1]) > 200)
	{
		ft_putstr_fd(RED"🤔 Error: Maximum of 200", 2);
		ft_putstr_fd("philosophers allowed.🤔\n" NC, 2);
		return (ERROR);
	}
	return (OK);
}
