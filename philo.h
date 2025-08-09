/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:19:58 by amert             #+#    #+#             */
/*   Updated: 2025/08/02 13:12:13 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# define DEAD 1
# define ALIVE 0

typedef struct s_philosopher
{
	int				id;
	int				status;
	int				eat_count;
	long			last_eat;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	struct s_data	*data;
	pthread_t		thread;
}	t_philosopher;

typedef struct s_data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				each_must_eat;
	int				eat_count;
	int				simulation_end;
	long			start_time;
	struct timeval	time_val;
	pthread_mutex_t	eat_mutex;
	t_philosopher	*philosopher;
	pthread_mutex_t	*fork;
}	t_data;

long	time_milisecond(t_data	*data);
int		p_init(t_data *data);
void	*routine(void	*ph);
void	f_check(t_philosopher *philosopher);
int		take_args(char **args, t_data *data);
int		printer(t_philosopher *philosopher, char *msg);
void	cleanup(t_data *data);
int		check_death(t_data *data);
int		check_eat_count(t_data *data);
int		init_mutexes(t_data *data);
void	init_philosophers(t_data *data);
void	ft_sleep(t_philosopher *p, long time);

#endif