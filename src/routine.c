/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 00:00:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/16 00:00:00 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

void	*philo_routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!philo->data->dead_flag)
	{
		if (philo_eat(philo))
		{
			if (philo->data->philo_count == 1)
			{
				while (!philo->data->dead_flag)
					ft_usleep(1);
			}
			break ;
		}
		if (philo->data->dead_flag)
			break ;
		log_philo_action(philo, SLEEPING);
		ft_usleep(philo->data->time_to_sleep);
		if (philo->data->dead_flag)
			break ;
		log_philo_action(philo, THINKING);
	}
	return (NULL);
}

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_lock);
	if (philo->data->num_times_to_eat != -1 && 
		philo->meals_eaten >= philo->data->num_times_to_eat)
	{
		pthread_mutex_unlock(&philo->data->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->meal_lock);
	
	pthread_mutex_lock(philo->r_fork);
	log_philo_action(philo, FORK_TAKEN);
	if (philo->data->philo_count == 1)
	{
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	pthread_mutex_lock(philo->l_fork);
	log_philo_action(philo, FORK_TAKEN);
	philo->eating = 1;
	log_philo_action(philo, EATING);
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->data->meal_lock);
	ft_usleep(philo->data->time_to_eat);
	philo->eating = 0;
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!data->dead_flag)
	{
		i = 0;
		while (i < data->philo_count && !data->dead_flag)
		{
			if (check_philo_death(data, i))
			{
				data->dead_flag = 1;
				return (NULL);
			}
			i++;
		}
		if (check_all_ate(data))
		{
			log_simulation_complete(data);
			data->dead_flag = 1;
			return (NULL);
		}
		ft_usleep(5);
	}
	return (NULL);
}

int	check_philo_death(t_data *data, int i)
{
	size_t	time;
	size_t	last_meal_time;

	time = get_current_time();
	pthread_mutex_lock(&data->meal_lock);
	last_meal_time = data->philos[i].last_meal;
	pthread_mutex_unlock(&data->meal_lock);
	
	if ((time - last_meal_time) >= data->time_to_die && 
		!data->philos[i].eating)
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
			break;
		i++;
	}
	
	return (all_finished);
}
