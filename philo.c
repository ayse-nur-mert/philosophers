/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:19:35 by amert             #+#    #+#             */
/*   Updated: 2025/08/02 11:55:51 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_fork_order(t_philosopher *philo, pthread_mutex_t **first,
			pthread_mutex_t **second)
{
	if (philo->id % 2 == 0)
	{
		*first = philo->l_fork;
		*second = philo->r_fork;
	}
	else
	{
		*first = philo->r_fork;
		*second = philo->l_fork;
	}
}

int	take_forks(t_philosopher *philo, pthread_mutex_t *first,
		pthread_mutex_t *second)
{
	pthread_mutex_lock(first);
	if (printer(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(first);
		return (1);
	}
	pthread_mutex_lock(second);
	if (printer(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(first);
		return (1);
	}
	return (0);
}

void	eat_and_sleep(t_philosopher *philo, pthread_mutex_t *first,
		pthread_mutex_t *second)
{
	pthread_mutex_lock(&philo->data->eat_mutex);
	philo->eat_count++;
	philo->last_eat = time_milisecond(philo->data);
	pthread_mutex_unlock(&philo->data->eat_mutex);
	ft_sleep(philo, philo->data->time_to_eat);
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
	printer(philo, "is sleeping");
	ft_sleep(philo, philo->data->time_to_sleep);
}

void	life_cycle(t_philosopher *philosopher)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	get_fork_order(philosopher, &first_fork, &second_fork);
	while (1)
	{
		if (take_forks(philosopher, first_fork, second_fork))
			break ;
		printer(philosopher, "is eating");
		eat_and_sleep(philosopher, first_fork, second_fork);
		if (printer(philosopher, "is thinking"))
			break ;
	}
}

void	*routine(void	*ph)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)ph;
	if (philosopher->data->num_of_philo == 1)
	{
		ft_sleep(philosopher, philosopher->data->time_to_die);
		f_check(philosopher);
		usleep(50);
		return (NULL);
	}
	if (philosopher->id % 2 == 0)
		usleep(100);
	life_cycle(philosopher);
	return (NULL);
}
