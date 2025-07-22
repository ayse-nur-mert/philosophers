/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:25:58 by amert             #+#    #+#             */
/*   Updated: 2025/07/22 11:49:08 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

int	is_valid_digit_string(char *str)
{
	int	j;

	if (!str[0])
	{
		printf("Error: Empty argument\n");
		return (0);
	}
	j = 0;
	while (str[j])
	{
		if (!ft_isdigit(str[j]))
		{
			printf("Error: Argument '%s' is not a valid number\n", str);
			return (0);
		}
		j++;
	}
	return (1);
}

int	check_numeric_args(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!is_valid_digit_string(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_argument_values(char **argv)
{
	int	philo_count;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;

	philo_count = ft_atoi(argv[1]);
	time_to_die = ft_atoi(argv[2]);
	time_to_eat = ft_atoi(argv[3]);
	time_to_sleep = ft_atoi(argv[4]);
	if (philo_count < 1 || philo_count > 200)
		return (0);
	if (time_to_die < 60)
		return (0);
	if (time_to_eat < 60)
		return (0);
	if (time_to_sleep < 60)
		return (0);
	return (check_optional_arg(argv));
}

int	check_optional_arg(char **argv)
{
	int	must_eat_count;

	if (argv[5])
	{
		must_eat_count = ft_atoi(argv[5]);
		if (must_eat_count < 1)
		{
			printf("Error: Number must be positive\n");
			return (0);
		}
	}
	return (1);
}

int	validate_arguments(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	if (!check_numeric_args(argv))
		return (1);
	if (!check_argument_values(argv))
		return (1);
	return (0);
}
