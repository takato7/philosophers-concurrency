/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_monitor_thread.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:30:06 by tmitsuya          #+#    #+#             */
/*   Updated: 2025/04/24 12:24:22 by tmitsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*ft_start_monitor(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (1)
	{
		if (ft_usleep(1e3) < 0)
		{
			ft_set_crtsct_status(philo, ERROR);
			break ;
		}
		if (ft_time_check_and_logging(philo, MONITOR))
			break ;
	}
	return (NULL);
}

int	ft_create_monitor_thread(t_philos *philo)
{
	if (ft_pthcrt(&philo->monitorid, NULL, ft_start_monitor, (void *)philo))
		return (0);
	return (1);
}
