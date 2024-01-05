/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:42:16 by avoronko          #+#    #+#             */
/*   Updated: 2024/01/04 17:17:22 by avoronko         ###   ########.fr       */
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

# define PHILO_MAX 200

typedef enum s_bool
{
	false,
	true
}	t_bool;

typedef struct s_philo
{
	pthread_t		thread;
	int				philo_id;
	int				meals_eaten;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	uint64_t		last_meal;
	t_bool			eating;
	t_bool			*dead;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*dead_mutex;
	pthread_mutex_t	*eat_mutex;
}					t_philo;

typedef struct s_data
{
	t_bool			dead;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	eat_mutex;
	int				num_of_philos;
	int				num_of_meals;
	uint64_t		start_time;
	t_philo			*philos;
}					t_data;

void	ft_routine(t_philo *philo, t_program *routine);

#endif