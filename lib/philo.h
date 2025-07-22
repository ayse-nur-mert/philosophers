/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:38:24 by amert             #+#    #+#             */
/*   Updated: 2025/07/22 11:39:06 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include "libft/libft.h"

/* Action types for logging */
# define FORK_TAKEN 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4

typedef struct s_philo
{
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	struct s_data	*data;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_data
{
	int				philo_count;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_times_to_eat;
	size_t			start_time;
	int				dead_flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
	pthread_mutex_t	meal_lock;
	pthread_t		monitor_thread;
	t_philo			*philos;
}	t_data;

/* Main functions */
int		main(int argc, char **argv);
int		handle_initialization_error(t_data *data, char *error_msg,
			int cleanup_needed);

/* Validation functions */
int		validate_arguments(int argc, char **argv);
int		check_numeric_args(char **argv);
int		check_argument_values(char **argv);
int		check_optional_arg(char **argv);
int		is_valid_digit_string(char *str);

/* Init functions */
int		init_data(t_data *data, char **argv);
int		init_mutexes_and_memory(t_data *data);
int		init_philos(t_data *data);
int		validate_args(int argc, char **argv);

/* Routine functions */
void	*philo_routine(void *philosopher);
int		philo_eat(t_philo *philo);
int		check_eating_conditions(t_philo *philo);
int		take_forks_and_eat(t_philo *philo);
void	*monitor_routine(void *arg);

/* Monitor functions */
int		check_philo_death(t_data *data, int i);
int		check_all_ate(t_data *data);

/* Utils */
size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);
void	print_message(char *str, t_philo *philo, int id);
void	log_action(t_philo *philo, char *action);
void	log_death(t_philo *philo);
void	log_philo_action(t_philo *philo, int action_type);
void	log_simulation_complete(t_data *data);

/* Cleanup and thread management */
void	cleanup(t_data *data);
void	destroy_all(t_data *data);
int		create_threads(t_data *data);
void	print_usage(char *program_name);

#endif
