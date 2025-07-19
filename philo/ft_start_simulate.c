/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_simulate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:11:44 by tmitsuya          #+#    #+#             */
/*   Updated: 2025/04/23 19:08:50 by tmitsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_set_philos_tv_start(t_philos *philo, t_shared *info)
{
	size_t	i;

	i = 0;
	if (ft_gettimeofday(&info->tv_start, NULL) < 0)
		return (0);
	while (i < info->size)
	{
		philo[i].tv = info->tv_start;
		i++;
	}
	return (1);
}

static int	ft_is_dinner_finished(t_philos *philo)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (i < philo->size)
	{
		if (philo[i].full)
			count++;
		i++;
	}
	if (count == philo->size)
		return (1);
	return (0);
}

static void	ft_set_sim_status(t_philos *philo, size_t np, size_t nm)
{
	ft_mutex_lock(&philo->info->mutex_sim);
	if (np == philo->info->size && nm == 1)
	{
		if (ft_set_philos_tv_start(philo, philo->info))
			philo->info->sim = START;
		else
			philo->info->sim = ERROR;
		if (np == 1)
			philo->info->sim = ALONE;
	}
	else
		philo->info->sim = ERROR;
	ft_mutex_unlock(&philo->info->mutex_sim);
}

int	ft_start_simulate(t_philos *philo, t_shared *info)
{
	size_t	num_philos;
	t_pth	pthid;
	size_t	num_monitor;

	num_philos = ft_create_philos_threads(philo);
	num_monitor = ft_create_monitor_thread(&pthid, philo);
	ft_set_sim_status(philo, num_philos, num_monitor);
	ft_join_philos(philo, num_philos);
	if (num_philos == 1 || ft_is_dinner_finished(philo))
		ft_set_crtsct_simulate(philo->info, END);
	ft_join_monitor(pthid, num_monitor);
	ft_cleanup(philo, info);
	if (info->sim == ERROR)
		return (1);
	return (0);
}
