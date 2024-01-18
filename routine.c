/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:15:36 by avoronko          #+#    #+#             */
/*   Updated: 2024/01/17 20:48:01 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *philo, t_data *data)
{
	if (data->num_of_philo == 1)
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
		ft_usleep(data, philo, 1);
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
	if (!take_forks(philo, data))
		return (1);
	pthread_mutex_lock(&philo->eat_mutex);
	philo->last_meal = get_current_time();
	if (data->num_of_meals != -1)
		philo->meals_eaten++;
	print_message(philo, data, "is eating\n");
	pthread_mutex_unlock(&philo->eat_mutex);
	if (ft_usleep(data, philo, philo->time_to_eat))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);

	return (1);
}

void	*ft_routine(void *arg)
{
	t_args			*args;
	t_philo			*philo;
	t_data			*data;

	args = (t_args *)arg;
	data = args->data;
	philo = args->philo;

	while (1)
	{
		if (!check_dead(data, philo))
		{
			if (!ft_meal(philo, data) || check_meals(data, philo))
				break ;
			print_message(philo, data, "is sleeping\n");
			if (ft_usleep(data, philo, philo->time_to_eat))
				break ;
			print_message(philo, data, "is thinking\n");
		}
		else
			break ;
	}
	return (arg);
}
