/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:53:14 by avoronko          #+#    #+#             */
/*   Updated: 2024/01/14 22:38:46 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_data(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&data->dead_mutex);
	pthread_mutex_destroy(&data->eat_mutex);
	while (++i < data->num_of_philos)
		pthread_mutex_destroy(&data->forks[i]);
}

int	av_check(char **av)
{
	if (ft_atoi(av[1]) > PHILO_MAX || ft_atoi(av[1]) <= 0
		|| digit_check(av[1]) == 1)
		throw_error("Invalid number of philosophers\n");
	if (ft_atoi(av[2]) <= 0 || digit_check(av[2]) == 1)
		throw_error("Invalid time to die\n");
	if (ft_atoi(av[3]) <= 0 || digit_check(av[3]) == 1)
		throw_error("Invalid time to eat\n");
	if (ft_atoi(av[4]) <= 0 || digit_check(av[4]) == 1)
		throw_error("Invalid time to sleep\n");
	if (av[5] && (ft_atoi(av[5]) < 0 || digit_check(av[5]) == 1))
		throw_error("Invalid number of times each philosopher must eat\n");
	return (0);
}

void	join_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	if (pthread_join(data->observer_thread, NULL) != 0)
	{
		cleanup_data(data);
		throw_error("Error: failed to join the observer thread\n");
	}
	while (i < data->num_of_philos)
	{
		if (pthread_join(philos[i].philo_thread, NULL) != 0)
		{
			cleanup_data(data);
			throw_error("Error: failed to join philosophers threads\n");
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data		data;
	t_philo		philos[PHILO_MAX];

	if (ac < 5 || ac > 6)
		throw_error("Invalid number of arguments\n");
	av_check(av);
	if (ft_init_data(&data, av))
		throw_error("Error: Failed to initialize data\n");
	if (ft_init_philos(&data, philos, av))
	{
		cleanup_data(&data);
		throw_error("Error: Failed to initialize philosophers\n");
	}
	if (pthread_create(&data.observer_thread, NULL, &ft_observer, &data) != 0)
	{
		cleanup_data(&data);
		throw_error("Error: Failed to create observer thread\n");
	}
	join_threads(&data, philos);
	cleanup_data(&data);

	return (0);
}
