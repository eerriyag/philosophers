/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerriyag <eerriyag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 08:02:45 by eerriyag          #+#    #+#             */
/*   Updated: 2025/06/26 13:22:29 by eerriyag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	error(char *msg)
{
	printf(RED"%s\n"RESET, msg);
	exit(1);
}

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	philo_think(t_philos *philo)
{
	if (should_stop(philo))
		return ;
	write_msg(philo, MSG_THINK);
}

void	philo_sleep(t_philos *philo)
{
	write_msg(philo, MSG_SLEEP);
	if (ft_usleep(philo->table->time_to_sleep, philo->table))
		return ;
}

int	ft_usleep(size_t time, t_table *table)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		if (should_stop(table->philos))
			return (1);
		pthread_mutex_lock(&table->death_lock);
		if (table->death_flag)
		{
			pthread_mutex_unlock(&table->death_lock);
			return (1);
		}
		pthread_mutex_unlock(&table->death_lock);
		usleep(50);
	}
	return (0);
}
