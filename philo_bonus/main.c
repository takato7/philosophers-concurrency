/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:30:25 by tmitsuya          #+#    #+#             */
/*   Updated: 2025/04/24 12:27:32 by tmitsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_philos	philo;

	if (!(argc == 5 || argc == 6))
	{
		write(STDERR_FILENO, "Invalid Number Arguments\n", 25);
		return (1);
	}
	if (!ft_init_philos(&philo, argc, argv))
		return (1);
	if (!ft_init_semaphore(&philo.sems, philo.semarr, philo.size))
	{
		free(philo.pid);
		return (1);
	}
	ft_start_simulate(&philo);
	return (0);
}
