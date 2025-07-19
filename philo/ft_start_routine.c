/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 16:27:31 by tmitsuya          #+#    #+#             */
/*   Updated: 2025/04/24 12:29:53 by tmitsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_thinking(t_philos *philo)
{
	long	time;

	time = 0;
	if (ft_time_check_and_logging(philo, THINKING))
		return (1);
	if (philo->size % 2 && philo->tm_eat >= philo->tm_sleep)
		time = ft_ms_to_usec(philo->tm_eat - philo->tm_sleep) + BUFFER;
	if (time)
	{
		if (ft_usleep(time) < 0)
		{
			ft_set_crtsct_simulate(philo->info, ERROR);
			return (1);
		}
	}
	return (0);
}

static int	ft_sleeping(t_philos *philo)
{
	if (ft_time_check_and_logging(philo, SLEEP))
		return (1);
	if (ft_usleep(ft_ms_to_usec(philo->tm_sleep)) < 0)
	{
		ft_set_crtsct_simulate(philo->info, ERROR);
		return (1);
	}
	return (0);
}

static int	ft_start_with_thinking(t_philos *philo)
{
	if (philo->num % 2 || (philo->size % 2 && philo->num == philo->size - 1))
	{
		if (ft_time_check_and_logging(philo, THINKING))
			return (1);
		if (ft_usleep(ft_ms_to_usec(philo->tm_eat) / 2) < 0)
		{
			ft_set_crtsct_simulate(philo->info, ERROR);
			return (1);
		}
	}
	return (0);
}

void	*ft_start_routine(void *arg)
{
	t_philos	*philo;
	t_sim		sim;

	philo = (t_philos *)arg;
	sim = ft_checkout_crtsct_simulate(philo->info);
	while (sim == NOTREADY || sim == ALONE)
		sim = ft_checkout_crtsct_simulate(philo->info);
	if (sim == ERROR)
		return (NULL);
	if (ft_start_with_thinking(philo))
		return (NULL);
	while (1)
	{
		if (ft_eating(philo))
			break ;
		if (ft_sleeping(philo))
			break ;
		if (ft_thinking(philo))
			break ;
	}
	return (NULL);
}
