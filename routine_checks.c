/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:42:47 by avoronko          #+#    #+#             */
/*   Updated: 2024/01/17 17:52:44 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, t_data *data, char *str)
{
	printf("%llu %i %s", (get_current_time() - data->start_time), 
		philo->philo_id, str);
}

int	check_dead(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->dead_mutex);
	pthread_mutex_lock(&philo->eat_mutex);
	if (data->dead == true)
	{
		pthread_mutex_unlock(&philo->eat_mutex);
		pthread_mutex_unlock(&data->dead_mutex);
		return (1);
	}
	else if (get_current_time() - philo->last_meal >= philo->time_to_die) 
	{
		data->dead = true;
		print_message(philo, data, "died\n");
		pthread_mutex_unlock(&philo->eat_mutex);
		pthread_mutex_unlock(&data->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->eat_mutex);
	pthread_mutex_unlock(&data->dead_mutex);
	return (0);
}

int	check_meals(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_mutex);
	if (data->num_of_meals == -1 
		|| philo->meals_eaten < data->num_of_meals)
	{
		pthread_mutex_unlock(&philo->eat_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->eat_mutex);
	return (1);
}
