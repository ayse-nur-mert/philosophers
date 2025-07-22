/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:26:05 by amert             #+#    #+#             */
/*   Updated: 2025/07/22 11:41:18 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

int	init_data(t_data *data, char **argv)
{
	data->philo_count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		data->num_times_to_eat = ft_atoi(argv[5]);
	else
		data->num_times_to_eat = -1;
	data->dead_flag = 0;
	data->start_time = get_current_time();
	return (init_mutexes_and_memory(data));
}

int	init_mutexes_and_memory(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->philos || !data->forks)
		return (1);
	i = -1;
	while (++i < data->philo_count)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eating = 0;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = get_current_time();
		data->philos[i].data = data;
		data->philos[i].r_fork = &data->forks[i];
		data->philos[i].l_fork = &data->forks[(i + 1) % data->philo_count];
	}
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}
