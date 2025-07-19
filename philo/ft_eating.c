/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eating.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 16:26:23 by tmitsuya          #+#    #+#             */
/*   Updated: 2025/04/24 12:33:27 by tmitsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_put_forks_back(t_philos *philo)
{
	philo->first_hand->fork = 1;
	ft_mutex_unlock(&philo->first_hand->mutex_fork);
	philo->second_hand->fork = 1;
	ft_mutex_unlock(&philo->second_hand->mutex_fork);
}

static void	ft_try_to_get_forks(t_philos *philo)
{
	ft_mutex_lock(&philo->first_hand->mutex_fork);
	ft_mutex_lock(&philo->second_hand->mutex_fork);
	if (philo->first_hand->fork == 1 && philo->second_hand->fork == 1)
	{
		philo->first_hand->fork = 0;
		ft_time_check_and_logging(philo, TAKEN);
		philo->second_hand->fork = 0;
		ft_time_check_and_logging(philo, TAKEN);
	}
}

static int	ft_take_time_to_eat(t_philos *philo)
{
	if (ft_time_check_and_logging(philo, EAT))
	{
		ft_put_forks_back(philo);
		return (1);
	}
	if (ft_usleep(ft_ms_to_usec(philo->tm_eat)) < 0)
	{
		ft_set_crtsct_simulate(philo->info, ERROR);
		ft_put_forks_back(philo);
		return (1);
	}
	ft_put_forks_back(philo);
	return (0);
}

int	ft_eating(t_philos *philo)
{
	ft_try_to_get_forks(philo);
	if (ft_take_time_to_eat(philo))
		return (1);
	if (philo->tms_must_eat > 0)
		philo->tms_must_eat--;
	if (philo->tms_must_eat == 0)
	{
		ft_mutex_lock(&philo->info->mutex_sim);
		philo->full = 1;
		ft_mutex_unlock(&philo->info->mutex_sim);
		return (1);
	}
	return (0);
}
