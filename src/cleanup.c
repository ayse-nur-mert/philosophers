/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:25:38 by amert             #+#    #+#             */
/*   Updated: 2025/07/22 11:43:18 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

void	cleanup(t_data *data)
{
	int	i;

	pthread_join(data->monitor_thread, NULL);
	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	destroy_all(data);
}

void	destroy_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->lock);
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->meal_lock);
	free(data->philos);
	free(data->forks);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				&philo_routine, &data->philos[i]))
			return (1);
		i++;
	}
	if (pthread_create(&data->monitor_thread, NULL, &monitor_routine, data))
		return (1);
	return (0);
}

void	print_message(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->write);
	time = get_current_time() - philo->data->start_time;
	if (!philo->data->dead_flag)
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(&philo->data->write);
}

void	print_usage(char *program_name)
{
	printf("Usage: %s number_of_philosophers time_to_die ", program_name);
	printf("time_to_eat time_to_sleep ");
	printf("[number_of_times_each_philosopher_must_eat]\n");
}
