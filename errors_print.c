/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:02:25 by avoronko          #+#    #+#             */
/*   Updated: 2024/01/22 13:15:45 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, t_data *data, char *str)
{
	if (check_dead_flag(data) || check_meals_flag(data))
		return ;
	pthread_mutex_lock(&data->write_mutex);
	printf("%lu %i %s", (get_current_time() - data->start_time), 
		philo->philo_id, str);
	pthread_mutex_unlock(&data->write_mutex);
}

void	print_dead_message(t_args *args, int i)
{
	pthread_mutex_lock(&args->data->write_mutex);
	printf("%lu %i %s", (get_current_time() 
			- args->data->start_time), i, "died\n");
	pthread_mutex_unlock(&args->data->write_mutex);
}

void	throw_error(t_args *args, char *str)
{
	mutex_destroy(args);
	printf("%s", str);
}

void	early_error(char *str)
{
	printf("%s", str);
}
