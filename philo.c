/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:53:14 by avoronko          #+#    #+#             */
/*   Updated: 2024/01/19 16:40:26 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_destroy(t_args *args)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&args->data->dead_mutex);
	pthread_mutex_destroy(&args->data->write_mutex);
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
	mutex_destroy(args);
}

int	av_check(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		early_error("Invalid number of arguments\n");
	if (ft_atoi(av[1]) > PHILO_MAX || ft_atoi(av[1]) <= 0
		|| digit_check(av[1]) == 1)
		early_error("Invalid number of philosophers\n");
	if (ft_atoi(av[2]) <= 0 || digit_check(av[2]) == 1)
		early_error("Invalid time to die\n");
	if (ft_atoi(av[3]) <= 0 || digit_check(av[3]) == 1)
		early_error("Invalid time to eat\n");
	if (ft_atoi(av[4]) <= 0 || digit_check(av[4]) == 1)
		early_error("Invalid time to sleep\n");
	if (av[5] && (ft_atoi(av[5]) < 0 || digit_check(av[5]) == 1))
		early_error("Invalid number of times each philosopher must eat\n");
	return (0);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_philo		philo[PHILO_MAX];
	t_args		args[PHILO_MAX];
	pthread_t	observer;
	int			i;

	i = -1;
	av_check(ac, av);
	if (ft_init_data(&data, av))
		early_error("Error: Failed to initialize data\n");
	while (++i < PHILO_MAX)
	{
		args[i].data = &data;
		args[i].philo = &philo[i];
	}
	if (ft_init_philo(args, av))
		throw_error(args, "Error: Failed to initialize philosophers\n");
	if (pthread_create(&observer, NULL, &ft_observer, &args) != 0)
		throw_error(args, "Error: Failed to initialize observer\n");
	join_threads(args, observer);
	return (0);
}
