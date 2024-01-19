/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:53:44 by avoronko          #+#    #+#             */
/*   Updated: 2024/01/18 15:54:56 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	throw_error(t_args *args, char *str)
{
	mutex_destroy(args);
	printf("%s", str);
	exit(EXIT_FAILURE);
}

void	early_error(char *str)
{
	printf("%s", str);
	exit(EXIT_FAILURE);
}
