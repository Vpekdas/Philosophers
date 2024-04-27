/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:11:22 by vopekdas          #+#    #+#             */
/*   Updated: 2024/04/27 17:18:23 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <sys/time.h>
# include <stddef.h>
# include <stdio.h>
# include <unistd.h>

size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
int		ft_usleep(size_t milliseconds);
size_t	get_current_time(void);

#endif
