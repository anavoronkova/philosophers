/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:52:51 by avoronko          #+#    #+#             */
/*   Updated: 2024/01/09 16:33:19 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_philos(t_data *data, t_philo *philos, char **av)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philos)
	{
		philos[i].philo_id = i;
		philos[i].meals_eaten = 0;
		philos[i].time_to_die = ft_atoi(av[2]);
		philos[i].time_to_eat = ft_atoi(av[3]);
		philos[i].time_to_sleep = ft_atoi(av[4]);
		philos[i].last_meal = 0;
		philos[i].eating = false;
		philos[i].dead = &data->dead;
		philos[i].right_fork = &data->forks[i];
		philos[i].left_fork = &data->forks[(i + 1) % data->num_of_philos];
		pthread_create(&philos[i].philo_thread, NULL, &ft_routine, &args);
	}
	return (0);
}

int	ft_init_data(t_data *data, t_philo *philos, char **av)
{
	int				i;
	struct timeval	current_time;

	i = -1;
	data->num_of_philos = ft_atoi(av[1]);
	if (av[5])
		data->num_of_meals = ft_atoi(av[5]);
	else
		data->num_of_meals = -1;
	gettimeofday(&current_time, NULL);
	data->start_time = (current_time.tv_sec * 1000) 
		+ (current_time.tv_usec / 1000);
	data->dead = false;
	pthread_mutex_init(&data->dead_mutex, NULL);
	pthread_mutex_init(&data->eat_mutex, NULL);
	while (++i < data->num_of_philos)
		pthread_mutex_init(&data->forks[i], NULL);
	return (0);
}
