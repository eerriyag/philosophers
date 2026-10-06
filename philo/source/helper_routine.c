/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerriyag <eerriyag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 08:04:03 by eerriyag          #+#    #+#             */
/*   Updated: 2025/06/25 18:17:33 by eerriyag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	write_msg(t_philos *philo, char *msg)
{
	pthread_mutex_lock(&philo->table->write_lock);
	pthread_mutex_lock(&philo->table->death_lock);
	if (!philo->table->death_flag)
	{
		printf(GREEN "%zu %d %s\n" RESET,
			get_time() - philo->table->start_time,
			philo->id_philos, msg);
	}
	pthread_mutex_unlock(&philo->table->death_lock);
	pthread_mutex_unlock(&philo->table->write_lock);
}

static void	lock_forks_even(t_philos *philo)
{
	pthread_mutex_lock(philo->left_fork);
	write_msg(philo, MSG_FORK);
	pthread_mutex_lock(philo->right_fork);
	write_msg(philo, MSG_FORK);
}

static void	lock_forks_odd(t_philos *philo)
{
	pthread_mutex_lock(philo->right_fork);
	write_msg(philo, MSG_FORK);
	pthread_mutex_lock(philo->left_fork);
	write_msg(philo, MSG_FORK);
}

void	update_meal_data(t_philos *philo)
{
	if (ft_usleep(philo->table->time_to_eat, philo->table))
		return ;
	pthread_mutex_lock(&philo->table->time_lock);
	philo->last_meal_eat = get_time();
	pthread_mutex_unlock(&philo->table->time_lock);
	pthread_mutex_lock(&philo->table->meal_lock);
	philo->meals_counter++;
	pthread_mutex_unlock(&philo->table->meal_lock);
}

void	philo_eat(t_philos *philo)
{
	if (should_stop(philo))
		return ;
	pthread_mutex_lock(&philo->table->meal_lock);
	if (philo->meals_counter >= philo->table->nbr_max_meals
		&& philo->table->nbr_max_meals != -1)
	{
		pthread_mutex_unlock(&philo->table->meal_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->table->meal_lock);
	if (philo->id_philos % 2 == 0)
		lock_forks_even(philo);
	else
		lock_forks_odd(philo);
	write_msg(philo, MSG_EAT);
	update_meal_data(philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
