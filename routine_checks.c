/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:42:47 by avoronko          #+#    #+#             */
/*   Updated: 2024/01/18 18:23:14 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
