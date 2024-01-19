/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:42:47 by avoronko          #+#    #+#             */
/*   Updated: 2024/01/19 16:55:01 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead_flag(t_data *data)
{
	pthread_mutex_lock(&data->dead_mutex);
	if (data->dead == true)
	{
		pthread_mutex_unlock(&data->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->dead_mutex);
	return (0);
}

int	check_meals_flag(t_data *data)
{
	pthread_mutex_lock(&data->meals_mutex);
	if (data->all_meals == true)
	{
		pthread_mutex_unlock(&data->meals_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->meals_mutex);
	return (0);
}

int	check_meals(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_mutex);
	if (data->num_of_meals == -1 || philo->meals_eaten < data->num_of_meals)
	{
		pthread_mutex_unlock(&philo->eat_mutex);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&philo->eat_mutex);
		return (1);
	}
}

int	check_starved(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_mutex);
	if (get_current_time() - philo->last_meal >= philo->time_to_die) 
	{
		pthread_mutex_lock(&data->dead_mutex);
		data->dead = true;
		pthread_mutex_unlock(&data->dead_mutex);
		pthread_mutex_unlock(&philo->eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->eat_mutex);
	return (0);
}

void	*ft_observer(void *arg)
{
	t_args	*args;
	t_data	*data;
	int		i;
	int		all_ate;

	args = (t_args *)arg;
	data = args->data;
	while (1) 
	{
		i = 0;
		all_ate = 1;
		while (i < data->num_of_philo) 
		{
			if (check_starved(data, args[i].philo)) 
			{
				printf("%lu %i %s", (get_current_time() - data->start_time), 
					args[i].philo->philo_id);
				return (arg);
			}
			if (!check_meals(data, args[i].philo))
			{
				all_ate = 0;
				break ;
			}
			i++;
		}
		if (all_ate) 
		{
			pthread_mutex_lock(&data->meals_mutex);
			data->all_meals = true;
			pthread_mutex_unlock(&data->meals_mutex);
			return (arg);
		}
	}
	return (arg);
}
