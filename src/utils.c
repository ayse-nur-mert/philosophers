/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:25:52 by amert             #+#    #+#             */
/*   Updated: 2025/07/22 11:40:21 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

void	log_action(t_philo *philo, char *action)
{
	size_t	timestamp;

	pthread_mutex_lock(&philo->data->write);
	if (!philo->data->dead_flag)
	{
		timestamp = get_current_time() - philo->data->start_time;
		printf("%zu %d %s\n", timestamp, philo->id, action);
	}
	pthread_mutex_unlock(&philo->data->write);
}

void	log_death(t_philo *philo)
{
	size_t	timestamp;

	pthread_mutex_lock(&philo->data->write);
	timestamp = get_current_time() - philo->data->start_time;
	printf("%zu %d died\n", timestamp, philo->id);
	pthread_mutex_unlock(&philo->data->write);
}

void	log_simulation_complete(t_data *data)
{
	size_t	timestamp;

	pthread_mutex_lock(&data->write);
	timestamp = get_current_time() - data->start_time;
	printf("%zu All philosophers have eaten %d times - simulation complete\n",
		timestamp, data->num_times_to_eat);
	pthread_mutex_unlock(&data->write);
}

void	log_philo_action(t_philo *philo, int action_type)
{
	char	*action_msg;

	if (action_type == FORK_TAKEN)
		action_msg = "has taken a fork";
	else if (action_type == EATING)
		action_msg = "is eating";
	else if (action_type == SLEEPING)
		action_msg = "is sleeping";
	else if (action_type == THINKING)
		action_msg = "is thinking";
	else
		return ;
	log_action(philo, action_msg);
}
