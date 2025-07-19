/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_monitor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:56:23 by tmitsuya          #+#    #+#             */
/*   Updated: 2025/04/24 12:34:11 by tmitsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_checking_philos(t_philos *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->info->size)
	{
		if (ft_time_check_and_logging(&philo[i], MONITOR))
			return (1);
	}
	return (0);
}

void	*ft_start_monitor(void *arg)
{
	t_philos	*philo;
	t_sim		sim;

	philo = (t_philos *)arg;
	sim = ft_checkout_crtsct_simulate(philo->info);
	while (sim == NOTREADY)
		sim = ft_checkout_crtsct_simulate(philo->info);
	if (sim == ERROR)
		return (NULL);
	while (1)
	{
		if (ft_usleep(1e3) < 0)
		{
			ft_set_crtsct_simulate(philo->info, ERROR);
			break ;
		}
		if (ft_checking_philos(philo))
			break ;
	}
	return (NULL);
}
