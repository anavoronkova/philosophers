/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:42:47 by avoronko          #+#    #+#             */
/*   Updated: 2024/01/16 20:17:36 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			pthread_mutex_unlock(&data->dead_mutex);
			return (1);
		}
	}
	pthread_mutex_unlock(&data->dead_mutex);
	return (0);
}

int	check_dead(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->dead_mutex);
	if (data->dead == true)
	{
		print_message(philo, data, "died\n");
		pthread_mutex_unlock(&data->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->dead_mutex);
	return (0);
}

int	check_meals(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->eat_mutex);
	if (data->num_of_meals == -1 
		|| philo->meals_eaten < data->num_of_meals)
	{
		pthread_mutex_unlock(&data->eat_mutex);
		return (0);
	}
	pthread_mutex_unlock(&data->eat_mutex);
	return (1);
}
