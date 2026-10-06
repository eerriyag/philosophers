/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerriyag <eerriyag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 08:03:50 by eerriyag          #+#    #+#             */
/*   Updated: 2025/06/26 13:28:45 by eerriyag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_all_ate(t_table *table)
{
	int	all_ate;
	int	j;

	if (table->nbr_max_meals == -1)
		return (0);
	all_ate = 1;
	pthread_mutex_lock(&table->meal_lock);
	j = -1;
	while (++j < table->nbr_philos)
	{
		if (table->philos[j].meals_counter < table->nbr_max_meals)
		{
			all_ate = 0;
			break ;
		}
	}
	pthread_mutex_unlock(&table->meal_lock);
	if (all_ate)
	{
		pthread_mutex_lock(&table->death_lock);
		table->death_flag = 1;
		pthread_mutex_unlock(&table->death_lock);
	}
	return (all_ate);
}

int	check_death(t_table *table, int i)
{
	size_t	current_time;
	size_t	last_meal;

	pthread_mutex_lock(&table->death_lock);
	if (table->death_flag)
		return (pthread_mutex_unlock (&table->death_lock), 0);
	pthread_mutex_unlock(&table->death_lock);
	current_time = get_time();
	pthread_mutex_lock(&table->time_lock);
	last_meal = table->philos[i].last_meal_eat;
	pthread_mutex_unlock(&table->time_lock);
	if ((long)(current_time - last_meal) > table->time_to_die)
	{
		pthread_mutex_lock(&table->death_lock);
		if (!table->death_flag)
		{
			printf(RED"%zu %d %s \n"RESET,
				current_time - table->start_time,
				table->philos[i].id_philos,
				MSG_DEAD);
			table->death_flag = 1;
		}
		return (pthread_mutex_unlock (&table->death_lock), 1);
	}
	return (0);
}

void	monitor(t_table *table)
{
	int	i;

	while (1)
	{
		if (check_all_ate(table))
			return ;
		i = 0;
		while (i < table->nbr_philos)
		{
			if (check_death(table, i))
				return ;
			i++;
		}
		usleep(50);
	}
}
