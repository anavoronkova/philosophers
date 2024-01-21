/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:15:36 by avoronko          #+#    #+#             */
/*   Updated: 2024/01/19 16:37:36 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *philo, t_data *data)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (data->num_of_philo == 1)
		return (0);
	if (philo->left_fork < philo->right_fork) 
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else 
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_lock(first_fork);
	print_message(philo, data, "has taken a fork\n");
	pthread_mutex_lock(second_fork);
	print_message(philo, data, "has taken a fork\n");
	return (1);
}

int	ft_meal(t_philo *philo, t_data *data)
{
	if (!take_forks(philo, data))
		return (0);
	pthread_mutex_lock(&philo->eat_mutex);
	philo->last_meal = get_current_time();
	if (data->num_of_meals != -1)
		philo->meals_eaten++;
	print_message(philo, data, "is eating\n");
	pthread_mutex_unlock(&philo->eat_mutex);
	if (ft_usleep(data, philo->time_to_eat))
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
	if (philo->philo_id % 2 != 0) 
		ft_usleep(data, 1);
	while (!check_dead_flag(data) && !check_meals_flag(data))
	{
		if (!ft_meal(philo, data))
			break ;
		print_message(philo, data, "is sleeping\n");
		if (ft_usleep(data, philo->time_to_sleep))
			break ;
		print_message(philo, data, "is thinking\n");
	}
	return (arg);
}
