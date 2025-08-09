/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:19:30 by amert             #+#    #+#             */
/*   Updated: 2025/08/02 12:19:41 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_milisecond(t_data	*data)
{
	gettimeofday(&data->time_val, NULL);
	return ((data->time_val.tv_usec / 1000
			+ data->time_val.tv_sec * 1000) - data->start_time);
}

int	check_args(char **args)
{
	int	i;
	int	j;

	j = 1;
	while (args[j])
	{
		i = -1;
		while (args[j][++i])
		{
			if (!(args[j][i] >= '0' && args[j][i] <= '9'))
			{
				printf("Error: Invalid argument format\n");
				return (EXIT_FAILURE);
			}
		}
		j++;
	}
	return (EXIT_SUCCESS);
}

long	args_to_nums(char *args)
{
	long	temp;
	int		sign;
	int		j;

	sign = 1;
	temp = 0;
	j = 0;
	while (args[j])
	{
		while (args[j] == '-' || args[j] == '+')
		{
			if (args[j] == '-')
				sign *= -1;
			j++;
		}
		while (args[j] && args[j] >= '0' && args[j] <= '9')
		{
			temp *= 10;
			temp += args[j] - 48;
			j++;
		}
	}
	return (temp * sign);
}

int	check_nums(char	**args)
{
	int	j;

	j = 1;
	while (args[j])
	{
		if (args_to_nums(args[j]) > 2147418647)
			return (EXIT_FAILURE);
		j++;
	}
	return (EXIT_SUCCESS);
}

int	take_args(char **args, t_data *data)
{
	int		j;

	j = 1;
	if (check_args(args) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_nums(args) == EXIT_FAILURE)
	{
		printf("Error: Values must be in correct range\n");
		return (EXIT_FAILURE);
	}
	data->num_of_philo = args_to_nums(args[j++]);
	data->time_to_die = args_to_nums(args[j++]);
	data->time_to_eat = args_to_nums(args[j++]);
	data->time_to_sleep = args_to_nums(args[j++]);
	if (args[j] != NULL)
		data->each_must_eat = args_to_nums(args[j]);
	else
		data->each_must_eat = -1;
	return (EXIT_SUCCESS);
}
