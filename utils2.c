/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:19:26 by amert             #+#    #+#             */
/*   Updated: 2025/08/02 11:55:51 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	printer(t_philosopher *philosopher, char	*msg)
{
	pthread_mutex_lock(&philosopher->data->eat_mutex);
	if (philosopher->data->simulation_end)
	{
		pthread_mutex_unlock(&philosopher->data->eat_mutex);
		return (1);
	}
	printf("%ld\t%d %s\n", time_milisecond(philosopher->data),
		philosopher->id, msg);
	pthread_mutex_unlock(&philosopher->data->eat_mutex);
	return (0);
}

void	f_check(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->data->eat_mutex);
	if (((time_milisecond(philosopher->data) - philosopher->last_eat))
		> philosopher->data->time_to_die)
		philosopher->status = DEAD;
	pthread_mutex_unlock(&philosopher->data->eat_mutex);
}

void	ft_sleep(t_philosopher *p, long time)
{
	long	dest_time;

	dest_time = time_milisecond(p->data) + time;
	while (time_milisecond(p->data) < dest_time)
	{
		pthread_mutex_lock(&p->data->eat_mutex);
		if (p->data->simulation_end)
		{
			pthread_mutex_unlock(&p->data->eat_mutex);
			break ;
		}
		pthread_mutex_unlock(&p->data->eat_mutex);
		usleep(50);
	}
}
