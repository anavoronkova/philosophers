/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:42:47 by avoronko          #+#    #+#             */
/*   Updated: 2024/01/22 14:04:14 by avoronko         ###   ########.fr       */
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

int	check_meals(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->data->num_of_philo)
	{
		pthread_mutex_lock(&args[i].philo->eat_mutex);
		if (args->data->num_of_meals == -1 
			|| args[i].philo->meals_eaten < args->data->num_of_meals)
		{
			pthread_mutex_unlock(&args[i].philo->eat_mutex);
			return (0);
		}
		pthread_mutex_unlock(&args[i].philo->eat_mutex);
	}
	return (1);
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
	int		i;

	args = (t_args *)arg;
	while (1) 
	{
		i = -1;
		while (++i < args->data->num_of_philo) 
		{
			if (check_starved(args->data, args[i].philo)) 
			{
				print_dead_message(args, args[i].philo->philo_id);
				return (arg);
			}
		}
		if (check_meals(args))
		{
			pthread_mutex_lock(&args->data->meals_mutex);
			args->data->all_meals = true;
			pthread_mutex_unlock(&args->data->meals_mutex);
			return (arg);
		}
	}
	return (arg);
}
