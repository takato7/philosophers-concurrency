/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:18:49 by tmitsuya          #+#    #+#             */
/*   Updated: 2025/04/23 19:26:44 by tmitsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_shared	info;
	t_philos	*philo;

	if (!(argc == 5 || argc == 6))
	{
		write(STDERR_FILENO, "Invalid Number Arguments\n", 25);
		return (1);
	}
	if (!ft_init_info(&info, argc, argv))
		return (1);
	philo = ft_init_philos(&info);
	if (!philo)
	{
		ft_mutex_destroy(&info.mutex_sim);
		return (1);
	}
	if (ft_start_simulate(philo, &info))
		return (1);
	return (0);
}
