/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerriyag <eerriyag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 08:03:56 by eerriyag          #+#    #+#             */
/*   Updated: 2025/06/25 08:03:57 by eerriyag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		table->philos[i].id_philos = i + 1;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1)
			% table->nbr_philos];
		table->philos[i].last_meal_eat = table->start_time;
		table->philos[i].meals_counter = 0;
		table->philos[i].table = table;
		i++;
	}
}

static int	init_forks(t_table *table)
{
	int	i;

	i = -1;
	table->forks = malloc(sizeof(t_mtx) * table->nbr_philos);
	if (!(table->forks))
		return (0);
	while (++i < table->nbr_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			while (i > 0)
				pthread_mutex_destroy(&table->forks[--i]);
			return (free(table->forks), 0);
		}
	}
	return (1);
}

static int	init_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->write_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&table->death_lock, NULL) != 0)
		return (pthread_mutex_destroy(&table->write_lock), 0);
	if (pthread_mutex_init(&table->meal_lock, NULL) != 0)
		return (pthread_mutex_destroy(&table->write_lock),
			pthread_mutex_destroy(&table->death_lock), 0);
	if (pthread_mutex_init(&table->time_lock, NULL) != 0)
		return (pthread_mutex_destroy(&table->write_lock),
			pthread_mutex_destroy(&table->death_lock),
			pthread_mutex_destroy(&table->meal_lock), 0);
	return (1);
}

int	init_philo_fock(t_table *table)
{
	table->start_time = get_time();
	table->death_flag = 0;
	if (!init_forks(table))
		return (0);
	if (!init_mutexes(table))
		return (0);
	table->philos = malloc(sizeof(t_philos) * table->nbr_philos);
	if (!(table->philos))
		return (0);
	init_philo(table);
	return (1);
}
