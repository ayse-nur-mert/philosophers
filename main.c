/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:19:45 by amert             #+#    #+#             */
/*   Updated: 2025/08/02 12:20:04 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philo)
		pthread_join(data->philosopher[i].thread, NULL);
	i = -1;
	while (++i < data->num_of_philo)
		pthread_mutex_destroy(&data->fork[i]);
	pthread_mutex_destroy(&data->eat_mutex);
	free (data->philosopher);
	free (data->fork);
}

int	check_status(t_data *data)
{
	if (check_death(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_eat_count(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	philo_create(t_data *data)
{
	data->start_time = 0;
	data->start_time = time_milisecond(data);
	data->simulation_end = 0;
	data->philosopher = malloc(sizeof(t_philosopher) * data->num_of_philo);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	if (!data->philosopher || !data->fork)
		return (EXIT_FAILURE);
	if (init_mutexes(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	init_philosophers(data);
	return (EXIT_SUCCESS);
}

int	p_init(t_data	*data)
{
	if (philo_create(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (1)
	{
		if (check_status(data) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		usleep(50);
	}
	return (EXIT_SUCCESS);
}

int	main(int ac, char *av[])
{
	t_data	data;
	int		result;

	if (ac > 6 || ac < 5)
	{
		printf("Usage: %s [number_of_philosophers] [time_to_die] ", av[0]);
		printf("[time_to_eat] [time_to_sleep] [number_of_times_must_eat]\n");
		return (EXIT_FAILURE);
	}
	if (take_args(av, &data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	result = p_init(&data);
	cleanup(&data);
	return (result);
}
