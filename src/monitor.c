/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:25:58 by amert             #+#    #+#             */
/*   Updated: 2025/07/22 11:47:55 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

int	check_philo_death(t_data *data, int i)
{
	size_t	time;
	size_t	last_meal_time;

	time = get_current_time();
	pthread_mutex_lock(&data->meal_lock);
	last_meal_time = data->philos[i].last_meal;
	pthread_mutex_unlock(&data->meal_lock);
	if ((time - last_meal_time) >= data->time_to_die && !data->philos[i].eating)
	{
		log_death(&data->philos[i]);
		return (1);
	}
	return (0);
}

int	check_all_ate(t_data *data)
{
	int	i;
	int	all_finished;

	if (data->num_times_to_eat == -1)
		return (0);
	all_finished = 1;
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->meal_lock);
		if (data->philos[i].meals_eaten < data->num_times_to_eat)
			all_finished = 0;
		pthread_mutex_unlock(&data->meal_lock);
		if (!all_finished)
			break ;
		i++;
	}
	return (all_finished);
}
