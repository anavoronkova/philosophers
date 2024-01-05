/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:15:36 by avoronko          #+#    #+#             */
/*   Updated: 2024/01/04 15:15:39 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_routine(t_philo *philo, t_program *routine)
{
	while (!routine->dead)
	{
		if (thinking)
			printf("%i is thinking", philo->philo_id);
		if (sleeping)
		{
			usleep(philo->time_to_sleep);
			printf("%i is sleeping", philo->philo_id);
		}
		if (philo->eating)
		{
			pthread_mutex_lock(&philo->right_fork);
			printf("%i has taken a fork", philo->philo_id);
			pthread_mutex_lock(&philo->left_fork);
			printf("%i has taken a fork", philo->philo_id);
			printf("%i is eating", philo->philo_id);
		}
	}
	if (routine->dead)
	{
		printf("%i died", philo->philo_id);
		ft_exit(philo, routine);
	}
}