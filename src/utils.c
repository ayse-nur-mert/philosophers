/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 00:00:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/16 00:00:00 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

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
