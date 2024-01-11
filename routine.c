/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:15:36 by avoronko          #+#    #+#             */
/*   Updated: 2024/01/11 17:55:11 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, t_data *data, char *str)
{
	struct timeval	current_time;
	uint64_t		timestamp;

	gettimeofday(&current_time, NULL);
	timestamp = (current_time.tv_sec * 1000) 
		+ (current_time.tv_usec / 1000) - data->start_time;
	printf("%llu %i %s", timestamp, philo->philo_id, str);
}

int	starved(t_philo *philo, t_data *data)
{
	struct timeval	current_time;
	uint64_t		timestamp;

	gettimeofday(&current_time, NULL);
	timestamp = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	printf("Debug: Philosopher %d, Last Meal: %llu, Current Time: %llu, Time to Die: %zu\n", 
           philo->philo_id, philo->last_meal, timestamp, philo->time_to_die);
	if (timestamp - philo->last_meal >= philo->time_to_die) 
	{
		printf("Philosopher %d is starving\n", philo->philo_id);
		pthread_mutex_lock(&data->dead_mutex);
        data->dead = true;
        pthread_mutex_unlock(&data->dead_mutex);
        return (1);
	}
	return (0);
}

int	take_forks(t_philo *philo, t_data *data)
{
	if (philo->philo_id % 2 == 0) 
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, data, "has taken a left fork\n");
		if (!pthread_mutex_trylock(philo->right_fork))
			print_message(philo, data, "has taken a right fork\n");
		else
		{
			pthread_mutex_unlock(philo->left_fork);
			return (0);
		}
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, data, "has taken a right fork\n");
		if (!pthread_mutex_trylock(philo->left_fork))
			print_message(philo, data, "has taken a left fork\n");
		else
		{
			pthread_mutex_unlock(philo->right_fork);
			return (0);
		}
	}
	return (1);
}

void	ft_meal(t_philo *philo, t_data *data)
{
	if (!take_forks(philo, data))
		return ;
	printf("Philosopher %d has taken both forks.\n", philo->philo_id);
	if (starved(philo, data))
	{
		printf("Philosopher %d is starving\n", philo->philo_id);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	print_message(philo, data, "is eating\n");
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_lock(&data->eat_mutex);
	if (data->num_of_meals != -1)
		philo->meals_eaten++;
	pthread_mutex_unlock(&data->eat_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*ft_routine(void *arg)
{
	t_args			*args;
	t_philo			*philos;
	t_data			*data;

	args = (t_args *)arg;
	data = args->data;
	philos = args->philo;
	while (1)
	{
		print_message(philos, data, "is thinking\n");
		ft_meal(philos, data);
		print_message(philos, data, "is sleeping\n");
		usleep(philos->time_to_sleep * 1000);
		if (data->dead) 
		{
			 printf("Philosopher %d died\n", philos->philo_id);
			//print_message(philos, data, "died\n");
			break ;
		}
	}
	return (0);
}
