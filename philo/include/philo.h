/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerriyag <eerriyag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 08:05:44 by eerriyag          #+#    #+#             */
/*   Updated: 2025/06/25 08:07:24 by eerriyag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>
# define MSG_FORK "has taken a fork"
# define MSG_DEAD "died"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"
# define MSG_THINK "is thinking"
# define RESET "\033[0m"
# define RED "\033[91m"
# define GREEN "\033[92m"

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef struct s_philos
{
	int			id_philos;
	t_mtx		*left_fork;
	t_mtx		*right_fork;
	t_table		*table;
	pthread_t	thread_id;
	long		meals_counter;
	size_t		last_meal_eat;
}	t_philos;

struct s_table
{
	t_philos	*philos;
	int			nbr_philos;
	int			death_flag;
	t_mtx		*forks;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_max_meals;
	long		start_time;
	t_mtx		write_lock;
	t_mtx		meal_lock;
	t_mtx		death_lock;
	t_mtx		time_lock;
};

int		ft_usleep(size_t time, t_table *table);
void	parse(t_table *table, char **av);
void	error(char *err);
int		init_philo_fock(t_table *table);
size_t	get_time(void);
int		start_routine(t_table *table);
void	monitor(t_table *table);
int		check_death(t_table *table, int i);
void	philo_eat(t_philos *philo);
int		check_all_ate(t_table *table);
void	write_msg(t_philos *philo, char *msg);
void	philo_think(t_philos *philo);
void	philo_sleep(t_philos *philo);
int		should_stop(t_philos *philo);
#endif