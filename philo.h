/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:42:16 by avoronko          #+#    #+#             */
/*   Updated: 2024/01/18 17:04:52 by avoronko         ###   ########.fr       */
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
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}					t_philo;

typedef struct s_data
{
	volatile t_bool	dead;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	forks[PHILO_MAX];
	pthread_mutex_t	write_mutex;
	int				num_of_philo;
	int				num_of_meals;
	uint64_t		start_time;
	t_philo			*philo;
}					t_data;

typedef struct s_args
{
	t_data	*data;
	t_philo	*philo;
}			t_args;

void	*ft_routine(void *arg);
void	throw_error(t_args *args, char *str);
void	early_error(char *str);
void	mutex_destroy(t_args *args);
void	print_message(t_philo *philo, t_data *data, char *str);
int		ft_init_philo(t_args *args, char **av);
int		ft_init_data(t_data *data, char **av);
int		check_dead(t_data *data, t_philo *philo);
int		check_meals(t_data *data, t_philo *philo);
int		digit_check(char *av);
int		ft_atoi(const char *str);
int		ft_usleep(t_data *data, t_philo *philo, size_t time);
size_t	get_current_time(void);

#endif