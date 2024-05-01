/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inf1n1ty <inf1n1ty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:20:38 by vopekdas          #+#    #+#             */
/*   Updated: 2024/05/01 00:39:27 by inf1n1ty         ###   ########.fr       */
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
	int		i;
	int		j;
	char	*str;
	char	*arg;

	i = 1;
	j = 0;
	while (i < ac)
	{
		str = ft_itoa(ft_atoi(av[i]));
		arg = av[i];
		if (*arg == '-' && str[j++] == '-')
			arg++;
		while (*arg && *arg == '0' && ft_strlen(arg) > 1)
			arg++;
		j += ft_skip_zero(str);
		if (ft_strcmp(arg, str + j) != 0)
			return (free(str), true);
		free(str);
		j = 0;
		i++;
	}
	return (false);
}

int	overall_parsing_check(int ac, char **av)
{
	if (is_arg_only_pos_nb(ac, av) == false)
	{
		ft_putstr_fd(RED"🤗Error: Only positive numbers are allowed.🤗\n" NC, 2);
		return (ERROR);
	}
	if (is_arg_overflow_underflow(ac, av) == true)
	{
		ft_putstr_fd(RED"🚰Error: Please enter numbers within" NC, 2);
		ft_putstr_fd(RED" the int range.🚰\n", 2);
		return (ERROR);
	}
	if (ft_atoi(av[1]) > 200)
	{
		ft_putstr_fd(RED"🤔Error: Maximum of 200 philosophers allowed.🤔\n" NC, 2);
		return (ERROR);
	}
	return (OK);
}
