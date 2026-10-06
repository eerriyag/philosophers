/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerriyag <eerriyag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 08:02:19 by eerriyag          #+#    #+#             */
/*   Updated: 2025/06/25 08:15:31 by eerriyag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	free_all(t_table *table)
{
	int	i;

	if (table->forks)
	{
		i = 0;
		while (i < table->nbr_philos)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
		free(table->forks);
		table->forks = NULL;
	}
	if (table->philos)
	{
		free(table->philos);
		table->philos = NULL;
	}
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->death_lock);
	pthread_mutex_destroy(&table->meal_lock);
	pthread_mutex_destroy(&table->time_lock);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6)
		return (error("[Argument Count ERROR] "), 1);
	else
	{
		parse(&table, av);
		if (!(init_philo_fock(&table)))
			return (error("[Init Error]: can't init philos/forks ."), 1);
		if (!start_routine(&table))
		{
			free_all(&table);
			return (1);
		}
		free_all(&table);
		return (0);
	}
}
