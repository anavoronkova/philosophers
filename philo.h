/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:42:16 by avoronko          #+#    #+#             */
/*   Updated: 2024/01/19 14:53:02 by avoronko         ###   ########.fr       */
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
	size_t			last_meal;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}					t_philo;

typedef struct s_data
{
	t_bool			dead;
	t_bool			all_meals;
	pthread_mutex_t	forks[PHILO_MAX];
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	meals_mutex;
	int				num_of_philo;
	int				num_of_meals;
	size_t			start_time;
	t_philo			*philo;
}					t_data;

typedef struct s_args
{
	t_data	*data;
	t_philo	*philo;
}			t_args;

//philo

void	mutex_destroy(t_args *args);
void	join_threads(t_args *args, pthread_t observer);
int		av_check(int ac, char **av);

//init
int		ft_init_data(t_data *data, char **av);
int		ft_init_philo(t_args *args, char **av);

//routine
void	*ft_routine(void *arg);
int		ft_meal(t_philo *philo, t_data *data);
int		take_forks(t_philo *philo, t_data *data);

//observer
void	*ft_observer(void *arg);
int		check_starved(t_data *data, t_philo *philo);
int		check_meals(t_data *data, t_philo *philo);
int		check_meals_flag(t_data *data);
int		check_dead_flag(t_data *data);

//errors
void	early_error(char *str);
void	throw_error(t_args *args, char *str);

//utils
int		ft_atoi(const char *str);
int		digit_check(char *av);
size_t	get_current_time(void);
int		ft_usleep(t_data *data, size_t time);
void	print_message(t_philo *philo, t_data *data, char *str);

#endif