/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:42:16 by avoronko          #+#    #+#             */
/*   Updated: 2024/01/14 21:45:55 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>
# include <stdint.h>

# define PHILO_MAX 200

typedef enum s_bool
{
	false,
	true
}	t_bool;

typedef struct s_philo
{
	pthread_t		philo_thread;
	int				philo_id;
	int				meals_eaten;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	uint64_t		last_meal;
	t_bool			eating;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}					t_philo;

typedef struct s_data
{
	volatile t_bool	dead;
	pthread_t		observer_thread;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	forks[PHILO_MAX];
	int				num_of_philos;
	int				num_of_meals;
	uint64_t		start_time;
	t_philo			*philos;
}					t_data;

typedef struct s_args
{
	t_data	*data;
	t_philo	*philo;
}			t_args;

void	*ft_routine(void *arg);
void	*ft_observer(void *arg);
void	throw_error(char *str);
void	cleanup_data(t_data *data);
int		ft_init_philos(t_data *data, t_philo *philos, char **av);
int		ft_init_data(t_data *data, char **av);
int		check_dead(t_data *data);
int		digit_check(char *av);
int		ft_atoi(const char *str);
int		ft_usleep(size_t time);
size_t	get_current_time(void);

#endif