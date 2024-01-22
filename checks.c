/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:09:51 by avoronko          #+#    #+#             */
/*   Updated: 2024/01/22 12:41:23 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_initialization(t_args *args, 
	t_data *data, pthread_t *observer, char **av)
{
	if (ft_init_data(data, av))
	{
		early_error("Error: Failed to initialize data\n");
		return (1);
	}
	if (ft_init_forks(args))
	{
		early_error("Error: Failed to initialize forks\n");
		return (1);
	}
	if (ft_init_philo(args, av))
	{
		throw_error(args, "Error: Failed to initialize philosophers\n");
		return (1);
	}
	if (pthread_create(observer, NULL, &ft_observer, args) != 0)
	{
		throw_error(args, "Error: Failed to initialize observer\n");
		return (1);
	}
	return (0);
}

int	av_first_check(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		early_error("Error: Invalid number of arguments\n");
		return (1);
	}
	if (ft_atoi(av[1]) > PHILO_MAX || ft_atoi(av[1]) <= 0
		|| digit_check(av[1]) == 1)
	{
		early_error("Error: Invalid number of philosophers\n");
		return (1);
	}
	if (ft_atoi(av[2]) <= 0 || digit_check(av[2]) == 1)
	{
		early_error("Error: Invalid time to die\n");
		return (1);
	}
	return (0);
}

int	av_second_check(char **av)
{
	if (ft_atoi(av[3]) <= 0 || digit_check(av[3]) == 1)
	{
		early_error("Error: Invalid time to eat\n");
		return (1);
	}
	if (ft_atoi(av[4]) <= 0 || digit_check(av[4]) == 1)
	{
		early_error("Error: Invalid time to sleep\n");
		return (1);
	}
	if (av[5] && (ft_atoi(av[5]) <= 0 || digit_check(av[5]) == 1))
	{
		early_error("Error: Invalid number of times to eat\n");
		return (1);
	}
	return (0);
}
