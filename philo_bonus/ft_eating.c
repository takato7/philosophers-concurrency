/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eating.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:22:53 by tmitsuya          #+#    #+#             */
/*   Updated: 2025/04/24 12:28:18 by tmitsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_put_forks_back(t_sems sems)
{
	ft_sem_post(sems.fork.semd);
	ft_sem_post(sems.fork.semd);
}

static void	ft_try_to_get_forks(t_philos *philo)
{
	ft_sem_wait(philo->sems.table.semd);
	ft_sem_wait(philo->sems.fork.semd);
	ft_sem_wait(philo->sems.fork.semd);
	ft_sem_post(philo->sems.table.semd);
	ft_time_check_and_logging(philo, TAKEN);
	ft_time_check_and_logging(philo, TAKEN);
}

static int	ft_take_time_to_eat(t_philos *philo)
{
	if (ft_time_check_and_logging(philo, EAT))
	{
		ft_put_forks_back(philo->sems);
		return (1);
	}
	if (ft_usleep(ft_ms_to_usec(philo->tm_eat)) < 0)
	{
		ft_set_crtsct_status(philo, ERROR);
		ft_put_forks_back(philo->sems);
		return (1);
	}
	ft_put_forks_back(philo->sems);
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
		ft_set_crtsct_status(philo, FULL);
		return (1);
	}
	return (0);
}
