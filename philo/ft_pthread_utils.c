/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pthread_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:06:27 by tmitsuya          #+#    #+#             */
/*   Updated: 2025/04/23 19:04:54 by tmitsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_create_philos_threads(t_philos *philo)
{
	size_t	i;
	void	*arg;

	i = 0;
	while (i < philo->size)
	{
		arg = (void *)&philo[i];
		if (ft_pthcrt(&philo[i].pthid, NULL, ft_start_routine, arg))
			return (i);
		i++;
	}
	return (i);
}

size_t	ft_create_monitor_thread(t_pth *pthid, t_philos *philo)
{
	if (ft_pthcrt(pthid, NULL, ft_start_monitor, (void *)philo))
		return (0);
	return (1);
}

void	ft_join_philos(t_philos *philo, size_t num_thread)
{
	size_t	i;

	i = 0;
	while (i < num_thread)
	{
		ft_pthjn(philo[i].pthid, NULL);
		i++;
	}
}

void	ft_join_monitor(t_pth pthid, size_t num_thread)
{
	if (num_thread)
		ft_pthjn(pthid, NULL);
}
