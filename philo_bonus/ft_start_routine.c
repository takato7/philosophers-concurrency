/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:33:18 by tmitsuya          #+#    #+#             */
/*   Updated: 2025/04/24 12:24:56 by tmitsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_thinking(t_philos *philo)
{
	if (ft_time_check_and_logging(philo, THINKING))
		return (1);
	return (0);
}

static int	ft_sleeping(t_philos *philo)
{
	if (ft_time_check_and_logging(philo, SLEEP))
		return (1);
	if (ft_usleep(ft_ms_to_usec(philo->tm_sleep)) < 0)
	{
		ft_set_crtsct_status(philo, ERROR);
		return (1);
	}
	return (0);
}

void	ft_start_routine(size_t num, t_philos *philo)
{
	philo->num = num;
	if (!ft_create_monitor_thread(philo))
		ft_clean_exit(philo, EXIT_FAILURE);
	if (philo->size != 1)
	{
		while (1)
		{
			if (ft_eating(philo))
				break ;
			if (ft_sleeping(philo))
				break ;
			if (ft_thinking(philo))
				break ;
		}
	}
	ft_pthjn(philo->monitorid, NULL);
	if (philo->status == ERROR)
		ft_clean_exit(philo, EXIT_FAILURE);
	if (philo->status == DEAD)
		ft_clean_exit(philo, EXIT_DEAD);
	ft_clean_exit(philo, EXIT_SUCCESS);
}
