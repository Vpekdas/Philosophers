/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:11:22 by vopekdas          #+#    #+#             */
/*   Updated: 2024/04/30 13:50:38 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <sys/time.h>
# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>

void	ft_putstr_fd(char *s, int fd);

size_t	ft_strlen(const char *s);
size_t	get_current_time(void);

int		ft_usleep(size_t milliseconds);
int		ft_atoi(const char *str);
int		ft_strcmp(char *s1, char *s2);

char	*ft_itoa(int n);

bool	overall_parsing_check(int ac, char **av);

// typedef struct s_philo
// (

// )		t_philo;

#endif
