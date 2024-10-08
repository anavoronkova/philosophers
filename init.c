/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:52:51 by avoronko          #+#    #+#             */
/*   Updated: 2024/01/23 18:02:54 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_philo(t_args *args, char **av)
{
	int		i;

	i = -1;
	while (++i < args->data->num_of_philo)
	{
		args[i].philo->philo_id = i + 1;
		args[i].philo->meals_eaten = 0;
		args[i].philo->time_to_die = ft_atoi(av[2]);
		args[i].philo->time_to_eat = ft_atoi(av[3]);
		args[i].philo->time_to_sleep = ft_atoi(av[4]);
		args[i].philo->last_meal = args[i].data->start_time;
		if (pthread_mutex_init(&args[i].philo->eat_mutex, NULL) != 0)
			return (1);
		if (pthread_create(&args[i].philo->philo_thread, 
				NULL, &ft_routine, &args[i]) != 0)
			return (1);
	}
	return (0);
}

int	ft_init_forks(t_args *args)
{
	int				i;

	i = -1;
	while (++i < args->data->num_of_philo)
	{
		if (pthread_mutex_init(&args->data->forks[i], NULL) != 0)
		{
			pthread_mutex_destroy(&args->data->dead_mutex);
			pthread_mutex_destroy(&args->data->write_mutex);
			pthread_mutex_destroy(&args->data->meals_mutex);
			return (1);
		}
	}
	i = -1;
	while (++i < args->data->num_of_philo)
	{
		args[i].philo->right_fork = &args[i].data->forks[i];
		args[i].philo->left_fork = 
			&args[i].data->forks[(i + 1) 
			% args[i].data->num_of_philo];
	}
	return (0);
}

int	ft_init_data(t_data *data, char **av)
{
	data->num_of_philo = ft_atoi(av[1]);
	if (av[5])
		data->num_of_meals = ft_atoi(av[5]);
	else
		data->num_of_meals = -1;
	data->start_time = get_current_time();
	data->dead = false;
	data->all_meals = false;
	if (pthread_mutex_init(&data->dead_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->write_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->dead_mutex);
		return (1);
	}
	if (pthread_mutex_init(&data->meals_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->dead_mutex);
		pthread_mutex_destroy(&data->write_mutex);
		return (1);
	}
	return (0);
}
