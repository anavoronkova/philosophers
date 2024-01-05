/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:53:14 by avoronko          #+#    #+#             */
/*   Updated: 2024/01/04 16:28:47 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	throw_error(char *str)
{
	printf("%s", str);
	exit(EXIT_FAILURE);
}
void	cleanup_data(t_data *data)
{} 

void	ft_exit()
{}

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

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	philos[PHILO_MAX];

	if (ac < 5 || ac > 6)
		throw_error("Invalid number of arguments\n");
	av_check(av);
	if (ft_init_data(&data, philos, av))
		throw_error("Error: Failed to initialize data\n");
	if (ft_create_threads(&data))
	{
		cleanup_data(&data);
		throw_error("Error: Failed to create threads\n");
	}
	join_threads(&data);
	cleanup_data(&data);

	return (0);
}
