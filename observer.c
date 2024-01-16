/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:42:47 by avoronko          #+#    #+#             */
/*   Updated: 2024/01/14 22:43:38 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_data *data)
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

int	check_meals(t_data *data)
{
	int		i;
	int		all_ate_required_meals;

	i = 0;
	all_ate_required_meals = 1;
	while (i < data->num_of_philos)
	{
		pthread_mutex_lock(&data->eat_mutex);
		if (data->num_of_meals != -1 
			&& data->philos[i].meals_eaten < data->num_of_meals)
			all_ate_required_meals = 0;
		pthread_mutex_unlock(&data->eat_mutex);
		i++;
	}
	return (all_ate_required_meals);
}

void	*ft_observer(void *arg)
{
	t_data			*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_dead(data))
			break ;
		if (check_meals(data))
			break ;
	}
	ft_usleep(50);
	return (arg);
}
