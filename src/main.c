/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:25:32 by amert             #+#    #+#             */
/*   Updated: 2025/07/22 11:40:08 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

int	handle_initialization_error(t_data *data, char *error_msg,
		int cleanup_needed)
{
	printf("Error: %s\n", error_msg);
	if (cleanup_needed)
		destroy_all(data);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (validate_arguments(argc, argv))
	{
		print_usage(argv[0]);
		return (1);
	}
	if (init_data(&data, argv))
		return (handle_initialization_error(&data,
				"Failed to initialize data", 0));
	if (init_philos(&data))
		return (handle_initialization_error(&data,
				"Failed to initialize philosophers", 1));
	if (create_threads(&data))
		return (handle_initialization_error(&data,
				"Failed to create threads", 1));
	cleanup(&data);
	return (0);
}
