/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:53:14 by avoronko          #+#    #+#             */
/*   Updated: 2024/01/21 11:16:19 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	throw_error(t_args *args, char *str)
{
	mutex_destroy(args);
	printf("%s", str);
}

void	early_error(char *str)
{
	printf("%s", str);
}

void	mutex_destroy(t_args *args)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&args->data->dead_mutex);
	pthread_mutex_destroy(&args->data->write_mutex);
	pthread_mutex_destroy(&args->data->meals_mutex);
	while (++i < args->data->num_of_philo)
	{
		pthread_mutex_destroy(&args->data->forks[i]);
		pthread_mutex_destroy(&args[i].philo->eat_mutex);
	}
}

void	join_threads(t_args *args, pthread_t observer)
{
	int	i;

	i = 0;
	while (i < args->data->num_of_philo)
	{
		if (pthread_join(args[i].philo->philo_thread, NULL) != 0)
			throw_error(args, "Error: failed to join philosophers threads\n");
		i++;
	}
	if (pthread_join(observer, NULL) != 0)
		throw_error(args, "Error: failed to join observer thread\n");
}

int	main(int ac, char **av)
{
	t_data		data;
	t_philo		philo[PHILO_MAX];
	t_args		args[PHILO_MAX];
	pthread_t	observer;
	int			i;

	i = -1;
	if (av_first_check(ac, av))
	    return (EXIT_FAILURE);
	if (av_second_check(av))
	    return (EXIT_FAILURE);
	while (++i < PHILO_MAX)
	{
		args[i].data = &data;
		args[i].philo = &philo[i];
	}
	if (ft_check_initialization(args, &data, &observer, av))
        return (EXIT_FAILURE);
	join_threads(args, observer);
	mutex_destroy(args);
	return (EXIT_SUCCESS);
}
