/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerriyag <eerriyag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 08:03:36 by eerriyag          #+#    #+#             */
/*   Updated: 2025/06/25 18:05:54 by eerriyag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*life_cycle_of_philo(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->id_philos % 2 == 0
		|| philo->id_philos == philo->table->nbr_philos)
	{
		if (ft_usleep(philo->table->time_to_eat / 2, philo->table))
			return (NULL);
	}
	while (1)
	{
		if (should_stop(philo))
			break ;
		philo_eat(philo);
		if (should_stop(philo))
			break ;
		philo_sleep(philo);
		if (should_stop(philo))
			break ;
		philo_think(philo);
	}
	return (NULL);
}

int	handle_one_philo(t_table *table)
{
	write_msg(&table->philos[0], MSG_FORK);
	usleep(table->time_to_die * 1000);
	pthread_mutex_lock(&table->write_lock);
	printf(RED "%zu %d %s\n" RESET, get_time() - table->start_time,
		1, MSG_DEAD);
	pthread_mutex_unlock(&table->write_lock);
	return (1);
}

static int	create_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL,
				(void *)life_cycle_of_philo, &table->philos[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

static int	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		if (pthread_join(table->philos[i].thread_id, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	start_routine(t_table *table)
{
	pthread_t	monitor_thread_id;

	if (table->nbr_philos == 1)
		return (handle_one_philo(table), 1);
	if (pthread_create(&monitor_thread_id, NULL,
			(void *)monitor, table) != 0)
		return (0);
	if (!create_threads(table))
		return (0);
	if (!join_threads(table))
		return (0);
	if (pthread_join(monitor_thread_id, NULL) != 0)
		return (0);
	return (1);
}
