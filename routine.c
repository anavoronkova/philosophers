/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:15:36 by avoronko          #+#    #+#             */
/*   Updated: 2024/01/14 23:01:07 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, t_data *data, char *str)
{
	printf("%llu %i %s", (get_current_time() - data->start_time), philo->philo_id, str);
}

int	starved(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->dead_mutex);
	if (get_current_time() - philo->last_meal >= philo->time_to_die) 
	{
		if (philo->eating == true)
		{
			pthread_mutex_unlock(&data->dead_mutex);
			return (0);
		}
		else
		{
			data->dead = true;
			print_message(philo, data, "died\n");
			pthread_mutex_unlock(&data->dead_mutex);
			return (1);
		}
	}
	pthread_mutex_unlock(&data->dead_mutex);
	return (0);
}

int	take_forks(t_philo *philo, t_data *data)
{
	if (data->dead) {
        return 0;
    }
    if (philo->philo_id % 2 != 0) {
        pthread_mutex_lock(philo->left_fork);
        print_message(philo, data, "has taken a left fork\n");
        pthread_mutex_lock(philo->right_fork);
        print_message(philo, data, "has taken a right fork\n");
    } 
	else {
        ft_usleep(1);
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, data, "has taken a left fork\n");
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, data, "has taken a right fork\n");
		}
	return (1);
}

int	ft_meal(t_philo *philo, t_data *data)
{
	if (data->dead)
	{
		printf("Philosopher %d seeng death before meal\n", philo->philo_id);
		return (0);
	}
	if (starved(philo, data))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	if (data->dead)
	{
		printf("Philosopher %d seeng death before taking forks\n", philo->philo_id);
		return (1);
	}
	if (!take_forks(philo, data))
		return (1);
	philo->eating = true;
	print_message(philo, data, "is eating\n");
	ft_usleep(philo->time_to_eat);
	pthread_mutex_lock(&data->eat_mutex);
	philo->last_meal = get_current_time();
	if (data->num_of_meals != -1)
		philo->meals_eaten++;
	philo->eating = false; 
	pthread_mutex_unlock(&data->eat_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (1);
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
		if (data->dead) {
            printf("Philosopher %d sees death before actions\n", philos->philo_id);
            break;
		}
	 	if (!ft_meal(philos, data)) {
            printf("Philosopher %d breaking loop after meal\n", philos->philo_id);
            break;
        }
        if (data->dead) {
            printf("Philosopher %d sees death after meal\n", philos->philo_id);
            break;
        }
        print_message(philos, data, "is thinking\n");
		if (data->dead) {
            printf("Philosopher %d sees death after thinking\n", philos->philo_id);
            break;
		}
        print_message(philos, data, "is sleeping\n");
		if (data->dead) {
            printf("Philosopher %d sees death before sleep\n", philos->philo_id);
            break;
		}
        ft_usleep(philos->time_to_sleep);
        if (data->dead) {
            printf("Philosopher %d sees death after sleep\n", philos->philo_id);
            break;
		}
	}
	return (arg);
}
