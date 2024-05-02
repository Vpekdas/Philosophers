/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:11:22 by vopekdas          #+#    #+#             */
/*   Updated: 2024/05/02 15:51:43 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>

# include <sys/time.h>

# include <unistd.h>

# include <pthread.h>

# include <string.h>

# define OK 0
# define ERROR -1
# define ERROR_CALLOC -2
# define ERROR_INIT_MUTEX -3
# define ERROR_INIT_THREAD -4

# define YELLOW "\033[0;33m"
# define GREEN	"\033[0;32m"
# define BLUE	"\033[0;34m"
# define RED	"\033[0;31m"
# define PURPLE	"\033[0;35m"
# define CYAN	"\033[0;36m"
# define BLACK	"\033[0;30"
# define WHITE	"\033[0;37m"
# define NC		"\033[0m"

typedef struct s_program	t_program;

enum	e_state
{
	SLEEPING,
	EATING,
	THINKING
};

typedef struct s_philo
{
	pthread_t		thread;
	size_t			philo_id;
	size_t			philo_nb;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			nb_to_eat;
	size_t			meal_eaten;
	size_t			last_meal_time;
	size_t			start_time;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_program		*program;
}		t_philo;

typedef struct s_program
{
	bool			is_philo_dead;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*forks;
	t_philo			**philos;
}					t_program;

size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_atoi(const char *str);
int		ft_strcmp(char *s1, char *s2);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_itoa(int n);
size_t	get_current_time(void);
int		overall_parsing_check(int ac, char **av);

t_philo	**init_philo_struct(char **av);
void	fill_time_and_philo(int ac, char **av, t_philo **philos,
			t_program *program);
int		create_thread(t_philo **philos, size_t philo_nb, void *routine);
int		create_forks(size_t philo_nb, t_program *program);
void	assign_forks(t_philo **philos, size_t philo_nb, t_program *program);

void	*routine(t_philo *philo);
void	print_message(enum e_state state, t_philo *philo);

void	argc_error(int ac);


#endif
