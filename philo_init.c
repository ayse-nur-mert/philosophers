/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:19:42 by amert             #+#    #+#             */
/*   Updated: 2025/08/02 11:55:51 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philo)
	{
		f_check(&data->philosopher[i]);
		pthread_mutex_lock(&data->eat_mutex);
		if (data->philosopher[i].status == DEAD)
		{
			printf("%ld\t%d died\n", time_milisecond(data),
				data->philosopher[i].id);
			data->simulation_end = 1;
			pthread_mutex_unlock(&data->eat_mutex);
			return (EXIT_FAILURE);
		}
		pthread_mutex_unlock(&data->eat_mutex);
	}
	return (EXIT_SUCCESS);
}

int	check_eat_count(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&data->eat_mutex);
	while (data->each_must_eat != -1 && ++i < data->num_of_philo)
		if (data->philosopher[i].eat_count < data->each_must_eat)
			break ;
	if (data->each_must_eat != -1 && i == data->num_of_philo)
	{
		data->simulation_end = 1;
		pthread_mutex_unlock(&data->eat_mutex);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&data->eat_mutex);
	return (EXIT_SUCCESS);
}

int	init_mutexes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philo)
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
			return (EXIT_FAILURE);
	pthread_mutex_init(&data->eat_mutex, NULL);
	return (EXIT_SUCCESS);
}

void	init_philosophers(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philo)
	{
		data->philosopher[i].id = i + 1;
		data->philosopher[i].r_fork = data->fork + i;
		data->philosopher[i].l_fork = data->fork + ((i + 1)
				% data->num_of_philo);
		data->philosopher[i].data = data;
		data->philosopher[i].status = ALIVE;
		data->philosopher[i].eat_count = 0;
		data->philosopher[i].last_eat = time_milisecond(data);
		pthread_create(&data->philosopher[i].thread, NULL, routine,
			&data->philosopher[i]);
	}
}
