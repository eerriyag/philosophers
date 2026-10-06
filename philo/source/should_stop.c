/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   should_stop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerriyag <eerriyag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 08:02:55 by eerriyag          #+#    #+#             */
/*   Updated: 2025/06/25 08:05:01 by eerriyag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_death_flag(t_philos *philo)
{
	int	stop;

	pthread_mutex_lock(&philo->table->death_lock);
	stop = philo->table->death_flag;
	pthread_mutex_unlock(&philo->table->death_lock);
	return (stop);
}

int	should_stop(t_philos *philo)
{
	if (check_death_flag(philo))
		return (1);
	if (check_all_ate(philo->table))
		return (1);
	return (0);
}
