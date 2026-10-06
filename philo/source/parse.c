/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerriyag <eerriyag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 08:03:43 by eerriyag          #+#    #+#             */
/*   Updated: 2025/06/25 08:03:44 by eerriyag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	is_digit(char str)
{
	return (str >= '0' && str <= '9');
}

int	is_all_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_digit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static char	*valid_input(char *str)
{
	int		lenght;
	char	*number;

	lenght = 0;
	while ((*str == 32) || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		error("Give my the value positive !");
	while (*str == '0')
		str++;
	if (!is_all_digit(str))
		error("The value is not a correct digit !");
	number = str;
	while (is_digit(*str++))
		lenght++;
	if (lenght > 10)
		error("The value too big , INT_MAX is the limit !");
	return (number);
}

static long	ft_atoi(char *str)
{
	long	number;

	number = 0;
	str = valid_input(str);
	while (is_digit(*str))
		number = (number * 10) + (*str++ - 48);
	if (number > INT_MAX)
		error(" The value is too big , INT_MAX is the limit !");
	return (number);
}

void	parse(t_table *table, char **av)
{
	table->nbr_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (table->time_to_die < 60 || table->time_to_eat < 60
		|| table->time_to_sleep < 60)
		error("Each time must be >= 60 milliseconds");
	if (table->nbr_philos > 200)
		error("Too many philosophers. Limit is 200.");
	if (table->nbr_philos <= 0)
		error("Number of philosophers must be positive.");
	if (av[5])
	{
		table->nbr_max_meals = ft_atoi(av[5]);
		if (table->nbr_max_meals == 0)
			error("The number of meals must be at least 1 or leave it empty.");
	}
	else
		table->nbr_max_meals = -1;
}
