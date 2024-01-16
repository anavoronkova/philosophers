/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:15:36 by avoronko          #+#    #+#             */
/*   Updated: 2024/01/16 20:37:06 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, t_data *data, char *str)
{
	printf("%lu %i %s", (get_current_time() - data->start_time), 
		philo->philo_id, str);
}

int	take_forks(t_philo *philo, t_data *data)
{
	if (data->dead)
		return (0);
	if (philo->philo_id % 2 != 0) 
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, data, "has taken a fork\n");
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, data, "has taken a fork\n");
	}
	else 
	{
		ft_usleep(1);
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, data, "has taken a fork\n");
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, data, "has taken a fork\n");
	}
	return (1);
}

int	ft_meal(t_philo *philo, t_data *data)
{
	if (check_dead(data, philo))
		return (0);
	if (starved(philo, data))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
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
		if (check_dead(data, philos))
			break ;
		if (!ft_meal(philos, data))
			break ;
		if (check_meals(data, philos))
			break ;
		print_message(philos, data, "is thinking\n");
		if (check_dead(data, philos))
			break ;
		print_message(philos, data, "is sleeping\n");
		ft_usleep(philos->time_to_sleep);
	}
	return (arg);
}
