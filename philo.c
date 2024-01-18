/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:53:14 by avoronko          #+#    #+#             */
/*   Updated: 2024/01/17 19:56:57 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_destroy(t_args *args)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&args->data->dead_mutex);
	while (++i < args->data->num_of_philo)
	{
		pthread_mutex_destroy(&args->data->forks[i]);
		pthread_mutex_destroy(&args[i].philo->eat_mutex);
	}
}

int	av_check(t_args *args, char **av)
{
	if (ft_atoi(av[1]) > PHILO_MAX || ft_atoi(av[1]) <= 0
		|| digit_check(av[1]) == 1)
		throw_error(args, "Invalid number of philoophers\n");
	if (ft_atoi(av[2]) <= 0 || digit_check(av[2]) == 1)
		throw_error(args, "Invalid time to die\n");
	if (ft_atoi(av[3]) <= 0 || digit_check(av[3]) == 1)
		throw_error(args, "Invalid time to eat\n");
	if (ft_atoi(av[4]) <= 0 || digit_check(av[4]) == 1)
		throw_error(args, "Invalid time to sleep\n");
	if (av[5] && (ft_atoi(av[5]) < 0 || digit_check(av[5]) == 1))
		throw_error(args, "Invalid number of times each philoopher must eat\n");
	return (0);
}

void	join_threads(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->data->num_of_philo)
	{
		if (pthread_join(args[i].philo->philo_thread, NULL) != 0)
			throw_error(args, "Error: failed to join philoophers threads\n");
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data		data;
	t_philo		philo[PHILO_MAX];
	t_args		args[PHILO_MAX];
	int			i;
	
	i = -1;
	if (ac < 5 || ac > 6)
		throw_error(args, "Invalid number of arguments\n");
	av_check(args, av);
	if (ft_init_data(&data, av))
		throw_error(args, "Error: Failed to initialize data\n");
	while(++i < PHILO_MAX)
	{
		args[i].data = &data;
        args[i].philo = &philo[i];
	}
	if (ft_init_philo(args, av))
		throw_error(args, "Error: Failed to initialize philosophers\n");
	join_threads(args);
	mutex_destroy(args);

	return (0);
}
